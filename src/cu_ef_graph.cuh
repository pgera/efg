#pragma once
#include "cuda_util.cuh"
#include "ef_graph.h"
#include "ef_param.h"

template <size_t kSkipQuantum, size_t kForwardQuantum>
class CUEFGraph {
    const EFGraph<kSkipQuantum, kForwardQuantum>* ef_graph_ptr_;
    const EFGraph<kSkipQuantum, kForwardQuantum>& ef_graph_;
    const size_t num_vertices_, num_edges_;
    const ef_param_t ef_param_;
    uint8_t* d_data_;
    void *d_offsets_, *d_degree_;
    uint8_t* d_num_lower_bits_;
    // 0 = Device, 1 = UVM, 2 = Zero-Copy
    int mem_alloc_mode_;

public:
    CUEFGraph(
        const EFGraph<kSkipQuantum, kForwardQuantum>& ef_graph,
        int alloc_mode = 0)
        : ef_graph_ptr_(nullptr),
          ef_graph_(ef_graph),
          num_vertices_(ef_graph_.get_num_vertices()),
          num_edges_(ef_graph_.get_num_edges()),
          ef_param_(ef_graph_.get_ef_params()),
          d_data_(nullptr),
          d_offsets_(nullptr),
          d_degree_(nullptr),
          d_num_lower_bits_(nullptr),
          mem_alloc_mode_(alloc_mode) {
        setup();
    }

    CUEFGraph(
        const EFLayout<kSkipQuantum, kForwardQuantum>& ef_layout,
        int alloc_mode = 0)
        : ef_graph_ptr_(new EFGraph<kSkipQuantum, kForwardQuantum>(ef_layout)),
          ef_graph_(*ef_graph_ptr_),
          num_vertices_(ef_graph_.get_num_vertices()),
          num_edges_(ef_graph_.get_num_edges()),
          ef_param_(ef_graph_.get_ef_params()),
          d_data_(nullptr),
          d_offsets_(nullptr),
          d_degree_(nullptr),
          d_num_lower_bits_(nullptr),
          mem_alloc_mode_(alloc_mode) {
        setup();
    }

    size_t get_num_vertices() const {
        return num_vertices_;
    }

    size_t get_num_edges() const {
        return num_edges_;
    }

    ef_param_t get_ef_params() const {
        return ef_param_;
    }

    const void* get_data() const {
        return d_data_;
    }

    const void* get_offsets() const {
        return d_offsets_;
    }

    const void* get_degree() const {
        return d_degree_;
    }

    const uint8_t* get_num_lower_bits() const {
        return d_num_lower_bits_;
    }

    void setup() {
        auto get_vec_size = [](auto vec) {
            return vec.size() * sizeof(vec[0]);
        };

        auto make_device_copy = [](const void* h_ptr, size_t size) -> void* {
            void* mem;
            CUDA_CHECK(cudaMalloc(&mem, size));
            CUDA_CHECK(cudaMemcpy(mem, h_ptr, size, cudaMemcpyHostToDevice));
            return mem;
        };

        auto make_zero_copy = [](const void* h_ptr, size_t size) -> void* {
            void* mem;
            CUDA_CHECK(cudaMallocManaged(&mem, size));
            CUDA_CHECK(cudaMemAdvise(mem, size, cudaMemAdviseSetAccessedBy, 0));

            memcpy(mem, h_ptr, size);
            return mem;
        };

        auto make_uvm_copy = [](const void* h_ptr, size_t size) -> void* {
            void* mem;
            CUDA_CHECK(cudaMallocManaged(&mem, size));
            CUDA_CHECK(cudaMemAdvise(mem, size, cudaMemAdviseSetReadMostly, 0));
            CUDA_CHECK(
                cudaMemAdvise(mem, size, cudaMemAdviseSetPreferredLocation, 0));

            memcpy(mem, h_ptr, size);
            return mem;
        };

        const auto& data_vec = ef_graph_.view_data_vec();
        if (mem_alloc_mode_ == 0) {
            d_data_ = static_cast<uint8_t*>(
                make_device_copy(data_vec.data(), get_vec_size(data_vec)));
        } else if (mem_alloc_mode_ == 1) {
            d_data_ = static_cast<uint8_t*>(
                make_uvm_copy(data_vec.data(), get_vec_size(data_vec)));
        } else if (mem_alloc_mode_ == 2) {
            d_data_ = static_cast<uint8_t*>(
                make_zero_copy(data_vec.data(), get_vec_size(data_vec)));
        } else {
            assert(0);
        }

        const auto& num_lower_bits_vec = ef_graph_.view_num_lower_bits_vec();
        d_num_lower_bits_ = static_cast<uint8_t*>(make_device_copy(
            num_lower_bits_vec.data(), get_vec_size(num_lower_bits_vec)));

        auto ef_param = ef_graph_.get_ef_params();

        auto chunk_offset_size = ef_param.chunk_offset_size;
        const auto& chunk_offsets = ef_graph_.view_offsets_vec();

        if (chunk_offset_size == sizeof(uint8_t)) {
            std::vector<uint8_t> tmp(
                chunk_offsets.begin(), chunk_offsets.end());
            d_offsets_ = make_device_copy(tmp.data(), get_vec_size(tmp));
        } else if (chunk_offset_size == sizeof(uint16_t)) {
            std::vector<uint16_t> tmp(
                chunk_offsets.begin(), chunk_offsets.end());
            d_offsets_ = make_device_copy(tmp.data(), get_vec_size(tmp));
        } else if (chunk_offset_size == sizeof(uint32_t)) {
            std::vector<uint32_t> tmp(
                chunk_offsets.begin(), chunk_offsets.end());
            d_offsets_ = make_device_copy(tmp.data(), get_vec_size(tmp));
        } else if (chunk_offset_size == sizeof(uint64_t)) {
            std::vector<uint64_t> tmp(
                chunk_offsets.begin(), chunk_offsets.end());
            d_offsets_ = make_device_copy(tmp.data(), get_vec_size(tmp));
        } else {
            assert(0);
        }

        auto degree_type_size = ef_param.degree_type_size;
        const auto& degree_vec = ef_graph_.view_degree_vec();

        if (degree_type_size == sizeof(uint8_t)) {
            std::vector<uint8_t> tmp(degree_vec.begin(), degree_vec.end());
            d_degree_ = make_device_copy(tmp.data(), get_vec_size(tmp));
        } else if (degree_type_size == sizeof(uint16_t)) {
            std::vector<uint16_t> tmp(degree_vec.begin(), degree_vec.end());
            d_degree_ = make_device_copy(tmp.data(), get_vec_size(tmp));
        } else if (degree_type_size == sizeof(uint32_t)) {
            std::vector<uint32_t> tmp(degree_vec.begin(), degree_vec.end());
            d_degree_ = make_device_copy(tmp.data(), get_vec_size(tmp));
        } else if (degree_type_size == sizeof(uint64_t)) {
            std::vector<uint64_t> tmp(degree_vec.begin(), degree_vec.end());
            d_degree_ = make_device_copy(tmp.data(), get_vec_size(tmp));
        } else {
            assert(0);
        }
    }

    virtual ~CUEFGraph() {
        delete ef_graph_ptr_;
        CUDA_CHECK(cudaFree(d_data_));
        CUDA_CHECK(cudaFree(d_offsets_));
        CUDA_CHECK(cudaFree(d_degree_));
        CUDA_CHECK(cudaFree(d_num_lower_bits_));
    }
};
