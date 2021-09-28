#include "csr.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "util.h"

CSR::CSR(const std::string& dir) {
    int rc = read_csr(dir, vlist_, elist_);
    if (!rc) {
        assert(vlist_.size());
        num_vertices_ = vlist_.size() - 1;
        num_edges_ = elist_.size();
    } else {
        std::string errorMessage = std::string("Failed to create CSR");
        throw std::runtime_error(errorMessage);
    }
}

size_t CSR::get_storage_size() const {
    return vlist_.size() * sizeof(decltype(vlist_)::value_type) +
           elist_.size() * sizeof(decltype(elist_)::value_type);
}

size_t CSR::get_optimal_size() const {
    auto row_offset_size = get_unsigned_type_size(num_edges_ + 1);
    auto col_ind_size = get_unsigned_type_size(num_vertices_);

    return (num_vertices_ + 1) * row_offset_size + (num_edges_ * col_ind_size);
}

std::pair<
    std::vector<uint64_t>::const_iterator,
    std::vector<uint64_t>::const_iterator>
CSR::get_nbrs(uint64_t vid) const {
    using diff_t = std::vector<uint64_t>::difference_type;
    auto begin = elist_.begin() + static_cast<diff_t>(vlist_.at(vid));
    auto end = elist_.begin() + static_cast<diff_t>(vlist_.at(vid + 1));
    return make_pair(begin, end);
}

uint64_t CSR::get_degree(uint64_t vid) const {
    return vlist_.at(vid + 1) - vlist_.at(vid);
}

uint64_t CSR::get_max_degree() const {
    uint64_t max_degree = 0;

    for (size_t i = 0; i < num_vertices_; i++) {
        max_degree = std::max(max_degree, get_degree(i));
    }

    return max_degree;
}

uint64_t CSR::get_visited_edges(const uint64_t* distances) const {
    uint64_t visited_edges = 0;
    #pragma omp parallel for reduction(+ : visited_edges)
    for (size_t i = 0; i < num_vertices_; i++) {
        if (distances[i] != std::numeric_limits<uint64_t>::max()) {
            visited_edges += get_degree(i);
        }
    }

    return visited_edges;
}

int CSR::read_csr(
    std::string dir,
    std::vector<uint64_t>& vlist,
    std::vector<uint64_t>& elist) {
    // namespace fs = boost::filesystem;
    namespace fs = std::filesystem;
    fs::path in_dir_path(dir), v_path, e_path;
    v_path = in_dir_path / "vertex.CSR";
    e_path = in_dir_path / "edge.CSR";

    size_t vfile_size, efile_size;

    try {
        vfile_size = fs::file_size(v_path);
        efile_size = fs::file_size(e_path);
    } catch (fs::filesystem_error& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    if (vfile_size % sizeof(uint64_t)) {
        std::cerr << "vfile_size not a multiple of sizeof(uint64_t)" << '\n';
        return 1;
    }

    if (efile_size % sizeof(uint64_t)) {
        std::cerr << "efile_size not not a multiple of sizeof(uint64_t)"
                  << '\n';
        return 1;
    }

    std::ifstream fin;

    fin.open(v_path.string().c_str(), std::ifstream::binary);
    if (!fin.is_open()) {
        std::cerr << "Can't open " << v_path.string() << "\n";
        return 1;
    }

    size_t num_row_offsets = vfile_size / sizeof(uint64_t);

    std::cout << "vertex_cnt = " << num_row_offsets - 1 << "\n";
    vlist.resize(num_row_offsets);
    fin.read(
        reinterpret_cast<char*>(vlist.data()),
        static_cast<std::streamsize>(vlist.size() * sizeof(uint64_t)));
    fin.close();

    fin.open(e_path.string().c_str(), std::ifstream::binary);
    if (!fin.is_open()) {
        std::cerr << "Can't open " << e_path.string() << "\n";
        return 1;
    }

    size_t edge_cnt = efile_size / sizeof(uint64_t);
    std::cout << "edge_cnt = " << edge_cnt << "\n";
    elist.resize(edge_cnt);
    fin.read(
        reinterpret_cast<char*>(elist.data()),
        static_cast<std::streamsize>(elist.size() * sizeof(uint64_t)));
    fin.close();
    return 0;
}
