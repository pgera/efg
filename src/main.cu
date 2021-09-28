#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

#include "bfs.cuh"
#include "csr.h"
#include "cu_ef_graph.cuh"
#include "ef_layout.h"

int main(int argc, char** argv) {
    const size_t kSkipQuantum = 0;
    const size_t kForwardQuantum = 512;
    bool use_uvm;
    bool no_sort;
    uint64_t num_traversals;
    uint64_t root = std::numeric_limits<uint64_t>::max();
    std::string in_dir, mapfile;

    namespace po = boost::program_options;
    po::options_description desc(
        std::string(argv[0]) + " [OPTIONS] INPUT_DIR\nOPTIONS");
    // clang-format off
    desc.add_options()
      ("help,h", "Print help")
      ("num,n", 
       po::value(&num_traversals)->default_value(100), 
       "Number of traversals")
      ("mapfile,m",
        po::value(&mapfile),
        "Mapfile for remapping vertex ids. If provided, map[x] will "
        "be used instead of x for starting a traversal")
      ("uvm,u",
       po::bool_switch(&use_uvm)->default_value(false),
       "Use UVM for memory allocations")
      ("nosort,d",
       po::bool_switch(&no_sort)->default_value(false),
       "Disable the frontier sorting optimisation")
      ("root,r",
       po::value<uint64_t>(&root),
       "Root for the traversal. Random roots will be used if unspecified");
    // clang-format on
    po::positional_options_description pos_desc;
    po::options_description hidden;
    hidden.add_options()("in_dir,i", po::value(&in_dir));
    pos_desc.add("in_dir", -1);
    po::options_description all;
    all.add(desc).add(hidden);

    po::command_line_parser parser{argc, argv};
    parser.options(all).positional(pos_desc);
    auto parsed_options = parser.run();

    po::variables_map vm;
    po::store(parsed_options, vm);
    po::notify(vm);
    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 0;
    }

    if (in_dir.empty()) {
        std::cerr << "ERROR: No input provided.\n";
        return 1;
    }

    std::cout << "Reading CSR from " << in_dir << "\n";
    CSR csr(in_dir);

    std::cout << "Total CSR size: " << csr.get_storage_size() << "\n";
    std::cout << "Optimal CSR size: " << csr.get_optimal_size() << "\n";

    EFLayout<kSkipQuantum, kForwardQuantum> ef_layout(csr);
    std::cout << "EF size: " << ef_layout.get_storage_size() << "\n";
    std::cout << "Compression ratio: "
              << csr.get_optimal_size() * 1.0 / ef_layout.get_storage_size()
              << "\n";

    std::cout << "Populating EFG Graph\n";

    CUEFGraph<kSkipQuantum, kForwardQuantum> cu_ef_graph(ef_layout, use_uvm);

    std::cout << "Graph populated\n";

    BFS<kSkipQuantum, kForwardQuantum> bfs(cu_ef_graph, !no_sort);

    std::mt19937_64 eng(0);
    std::uniform_int_distribution<uint64_t> distr;
    std::vector<uint64_t> vmap;

    if (!mapfile.empty()) {
        std::cout << "Reading mapfile " << mapfile << "\n";
        std::ifstream map_fin;
        map_fin.open(mapfile.c_str(), std::ifstream::binary);
        if (map_fin.is_open()) {
            map_fin.seekg(0, map_fin.end);
            uint64_t vertex_cnt = (map_fin.tellg() / sizeof(uint64_t));
            assert(vertex_cnt == cu_ef_graph.get_num_vertices());
            vmap.resize(vertex_cnt);
            map_fin.seekg(0, map_fin.beg);
            map_fin.read((char*)&(vmap[0]), sizeof(uint64_t) * (vertex_cnt));
            map_fin.close();
        } else {
            std::cerr << "ERROR: Could not open mapfile " << mapfile << "\n";
            return 1;
        }
    }

    std::vector<uint64_t> roots_vec(num_traversals, root);

    if (root == std::numeric_limits<uint64_t>::max()) {
        for (uint64_t i = 0; i < num_traversals; i++) {
            auto root_id = distr(eng) % cu_ef_graph.get_num_vertices();
            if (vmap.size()) root_id = vmap[root_id];
            roots_vec[i] = root_id;
        }
    }

    std::cout << "Running " << num_traversals << " traversals\n";
    // Warm Up
    bfs.traverse(roots_vec[0]);

    double total_time = 0;
    uint64_t total_visited_edges = 0;
    for (uint64_t i = 0; i < num_traversals; i++) {
        uint64_t src = roots_vec[i];
        auto distances = bfs.traverse(src);
        auto elapsed_time = bfs.get_last_elapsed_time();
        total_time += elapsed_time;
        auto visited_edges = csr.get_visited_edges(distances.data());
        total_visited_edges += visited_edges;

        if (vmap.size()) {
            std::vector<uint64_t> temp(cu_ef_graph.get_num_vertices());

            #pragma omp parallel for
            for (uint64_t j = 0; j < cu_ef_graph.get_num_vertices(); j++) {
                temp[j] = distances[vmap[j]];
            }

            distances = temp;
        }

        std::string hash = get_sha_sum(
            distances.data(), distances.size() * sizeof(distances[0]));

        std::cout << "[" << i << "]"
                  << " Source " << src << " Time " << elapsed_time
                  << " ms Visisted edges: " << visited_edges
                  << " GTEPS: " << ((double)visited_edges) * 1E-6 / elapsed_time
                  << " Hash " << hash << "\n";
    }

    std::cout << "Total time: " << total_time
              << " ms Total visited edges: " << total_visited_edges
              << " Total GTEPS: "
              << ((double)total_visited_edges) * 1E-6 / total_time << "\n";
}
