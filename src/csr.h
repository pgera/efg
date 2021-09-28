#pragma once
#include <cassert>
#include <string>
#include <vector>

class CSR {
    size_t num_vertices_;
    size_t num_edges_;
    std::vector<uint64_t> vlist_;
    std::vector<uint64_t> elist_;

    int read_csr(
        std::string dir,
        std::vector<uint64_t>& vlist,
        std::vector<uint64_t>& elist);

public:
    CSR(const std::string& dir);
    uint64_t get_max_degree() const;
    uint64_t get_degree(uint64_t vid) const;
    std::pair<
        std::vector<uint64_t>::const_iterator,
        std::vector<uint64_t>::const_iterator>
    get_nbrs(uint64_t vid) const;

    uint64_t get_degree_exsum(uint64_t vid) const {
        return vlist_.at(vid);
    }

    const std::vector<uint64_t>& get_elist() const {
        return elist_;
    }

    uint64_t get_num_vertices() const {
        return num_vertices_;
    }

    uint64_t get_num_edges() const {
        return num_edges_;
    }

    // Current storage size based on uint64_t
    size_t get_storage_size() const;
    // Optimal storage size based on the smallest type for vlist and elist
    size_t get_optimal_size() const;
    uint64_t get_visited_edges(const uint64_t* distances) const;
};
