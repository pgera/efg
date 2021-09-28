#pragma once
#include <thrust/binary_search.h>
#include <thrust/device_vector.h>

#include "bfs_kernels.cuh"
#include "cu_ef_graph.cuh"
#include "inst_trav.h"
#include "util.h"

#define FILL_ISOLATED(V, D) fill_isolated_bmap<V, D>()

template <size_t kSkipQuantum, size_t kForwardQuantum>
class BFS {
    const void *d_data_, *d_offsets_, *d_degree_;
    const uint8_t* d_num_lower_bits_;
    const size_t num_vertices_, num_edges_;
    const ef_param_t ef_param_;
    const size_t bitmap_size_;
    float elapsed_time_;

    cudaDeviceProp dev_prop_;
    size_t max_grid_size_;
    size_t cub_alloc_size_;
    int num_vertex_bits_;

    void *d_distances_, *d_frontier_, *d_scratch_, *d_front_deg_exsum_,
        *d_cub_temp_;
    void* d_binsearch_output_;
    uint8_t *d_isolated_bmap_, *d_visited_bmap_;
    bool sort_frontier_;

    template <
        typename Value,
        typename Edge,
        typename SkipValue,
        typename Degree,
        typename Offset>
    void traverse_impl(size_t source, std::vector<size_t>& h_distances);

    template <typename Value, typename Degree>
    void fill_isolated_bmap();

    template <typename Value, typename Degree, typename Edge>
    void fill_front_deg_exsum(
        const Value* frontier,
        Value nf,
        size_t& total_degree);

public:
    BFS(const CUEFGraph<kSkipQuantum, kForwardQuantum>& cu_ef_graph,
        bool sort_frontier = true)
        : d_data_(cu_ef_graph.get_data()),
          d_offsets_(cu_ef_graph.get_offsets()),
          d_degree_(cu_ef_graph.get_degree()),
          d_num_lower_bits_(cu_ef_graph.get_num_lower_bits()),
          num_vertices_(cu_ef_graph.get_num_vertices()),
          num_edges_(cu_ef_graph.get_num_edges()),
          // Needs to be INT padded since CUDA atomics work on INTS
          bitmap_size_(sizeof(int) * (num_vertices_ + INT_SIZE - 1) / INT_SIZE),
          elapsed_time_(0),
          max_grid_size_(MAX_BLOCKS),
          ef_param_(cu_ef_graph.get_ef_params()),
          num_vertex_bits_((int)log2((float)num_vertices_) + 1),
          d_scratch_(nullptr),
          // cub sort works only if num_vertices_ is <= max int
          sort_frontier_(
              num_vertices_ <= std::numeric_limits<int>::max() &&
              sort_frontier) {
        CUDA_CHECK(
            cudaMalloc(&d_distances_, ef_param_.val_type_size * num_vertices_));

        CUDA_CHECK(
            cudaMalloc(&d_frontier_, ef_param_.val_type_size * num_vertices_));

        if (sort_frontier_) {
            CUDA_CHECK(cudaMalloc(
                &d_scratch_, ef_param_.val_type_size * num_vertices_));
        }

        CUDA_CHECK(cudaMalloc(
            &d_front_deg_exsum_, ef_param_.edge_type_size * num_vertices_));
        CUDA_CHECK(cudaMalloc(&d_visited_bmap_, bitmap_size_));
        CUDA_CHECK(cudaMalloc(&d_isolated_bmap_, bitmap_size_));
        CUDA_CHECK(cudaMalloc(
            &d_binsearch_output_,
            ef_param_.val_type_size * (num_edges_ + PART_SIZE - 1) /
                PART_SIZE));

        VS2_GEN(
            ef_param_.val_type_size, ef_param_.degree_type_size, FILL_ISOLATED);

        int device;
        CUDA_CHECK(cudaGetDevice(&device));
        CUDA_CHECK(cudaGetDeviceProperties(&dev_prop_, device));
    }

    std::vector<size_t> traverse(size_t source);

    float get_last_elapsed_time() const {
        return elapsed_time_;
    }

    virtual ~BFS() {
        CUDA_CHECK(cudaFree(d_distances_));
        CUDA_CHECK(cudaFree(d_frontier_));
        CUDA_CHECK(cudaFree(d_scratch_));
        CUDA_CHECK(cudaFree(d_front_deg_exsum_));
        CUDA_CHECK(cudaFree(d_visited_bmap_));
        CUDA_CHECK(cudaFree(d_isolated_bmap_));
        CUDA_CHECK(cudaFree(d_binsearch_output_));
    }
};

template <size_t kSkipQuantum, size_t kForwardQuantum>
std::vector<size_t> BFS<kSkipQuantum, kForwardQuantum>::traverse(
    size_t source) {
    std::vector<size_t> distances;

    int v_size = ef_param_.val_type_size;
    int e_size = ef_param_.edge_type_size;
    int skip_size = ef_param_.fwd_type_size;
    int deg_size = ef_param_.degree_type_size;
    int chunk_offset_size = ef_param_.chunk_offset_size;

    // This instantiates all possible types which takes a while to compile
    // For dev and debug, instantiate only the required type as shown below
#ifndef DEVMODE
    INSTANTIATE_TRAVERSE(
        v_size,
        deg_size,
        skip_size,
        e_size,
        chunk_offset_size,
        traverse_impl,
        source,
        distances);
#else
    // E.g., for soc-lj, use this
    traverse_impl<uint32_t, uint32_t, uint16_t, uint16_t, uint32_t>(
        source, distances);
#endif
    return distances;
}

template <size_t kSkipQuantum, size_t kForwardQuantum>
template <typename Value, typename Degree>
void BFS<kSkipQuantum, kForwardQuantum>::fill_isolated_bmap() {
    thrust::device_ptr<const Degree> t_degree =
        thrust::device_pointer_cast(static_cast<const Degree*>(d_degree_));
    thrust::device_ptr<uint8_t> t_isolated_bmap =
        thrust::device_pointer_cast(d_isolated_bmap_);
    thrust::counting_iterator<Value> it1(0);
    thrust::counting_iterator<Value> it2 = it1 + bitmap_size_;
    thrust::for_each(
        it1,
        it2,
        fill_isolated_functor<Value, const Degree>(
            t_isolated_bmap, t_degree, static_cast<Value>(num_vertices_)));
}

template <size_t kSkipQuantum, size_t kForwardQuantum>
template <typename Value, typename Degree, typename Edge>
void BFS<kSkipQuantum, kForwardQuantum>::fill_front_deg_exsum(
    const Value* frontier,
    Value nf,
    size_t& total_degree) {
    thrust::device_ptr<const Degree> t_degree =
        thrust::device_pointer_cast(static_cast<const Degree*>(d_degree_));
    thrust::device_ptr<const Value> t_frontier =
        thrust::device_pointer_cast(frontier);
    thrust::device_ptr<Edge> t_front_deg_exsum =
        thrust::device_pointer_cast(d_front_deg_exsum_);

    thrust::counting_iterator<Value> it1(0);
    thrust::counting_iterator<Value> it2 = it1 + nf;
    thrust::for_each(
        it1,
        it2,
        fill_degree_functor<const Value, const Degree, Edge>(
            t_frontier, t_degree, t_front_deg_exsum));

    // Don't use auto with thrust. Auto returns a device ref
    Edge last_deg = t_front_deg_exsum[nf - 1];

    thrust::exclusive_scan(
        t_front_deg_exsum, t_front_deg_exsum + nf, t_front_deg_exsum);

    total_degree = t_front_deg_exsum[nf - 1] + last_deg;
}

template <size_t kSkipQuantum, size_t kForwardQuantum>
template <
    typename Value,
    typename Edge,
    typename SkipValue,
    typename Degree,
    typename Offset>
void BFS<kSkipQuantum, kForwardQuantum>::traverse_impl(
    size_t source,
    std::vector<size_t>& h_distances) {
    // All types should be unsigned
    static_assert(std::is_unsigned<Value>::value, "Value should be unsigned");
    static_assert(std::is_unsigned<Edge>::value, "Edge should be unsigned");
    static_assert(
        std::is_unsigned<SkipValue>::value, "SkipValue should be unsigned");
    static_assert(std::is_unsigned<Degree>::value, "Degree should be unsigned");
    static_assert(std::is_unsigned<Offset>::value, "Offset should be unsigned");

    h_distances.resize(num_vertices_);
#pragma omp parallel for
    for (size_t i = 0; i < num_vertices_; i++) {
        h_distances[i] = std::numeric_limits<size_t>::max();
    }
    h_distances[source] = 0;

    // Begin Profiling of CUDA section

    cudaEvent_t start_event, stop_event;
    CUDA_CHECK(cudaEventCreate(&start_event));
    CUDA_CHECK(cudaEventCreate(&stop_event));
    CUDA_CHECK(cudaEventRecord(start_event, 0));

    thrust::device_ptr<Value> t_distances =
        thrust::device_pointer_cast(d_distances_);
    thrust::fill(
        t_distances,
        t_distances + num_vertices_,
        std::numeric_limits<Value>::max());

    if (source >= num_vertices_) {
        std::cerr << "BFS source vertex " << source
                  << " out of range. Graph has " << num_vertices_
                  << " vertices\n";
        CUDA_CHECK(cudaEventRecord(stop_event, 0));
        CUDA_CHECK(cudaEventSynchronize(stop_event));
        CUDA_CHECK(
            cudaEventElapsedTime(&elapsed_time_, start_event, stop_event));

        return;
    }

    Value level_num = 0;
    t_distances[source] = level_num;

    thrust::device_ptr<Value> t_frontier =
        thrust::device_pointer_cast(d_frontier_);
    thrust::fill(t_frontier, t_frontier + num_vertices_, 0);

    thrust::device_ptr<Edge> t_front_deg_exsum =
        thrust::device_pointer_cast(d_front_deg_exsum_);
    thrust::fill(t_front_deg_exsum, t_front_deg_exsum + num_vertices_, 0);

    thrust::device_ptr<uint8_t> t_visited_bmap =
        thrust::device_pointer_cast(d_visited_bmap_);
    thrust::fill(t_visited_bmap, t_visited_bmap + bitmap_size_, 0);
    t_visited_bmap[source / 8] = 1U << (source % 8);

    thrust::device_ptr<const Degree> t_degree =
        thrust::device_pointer_cast(static_cast<const Degree*>(d_degree_));
    thrust::device_ptr<const uint8_t> t_isolated_bmap =
        thrust::device_pointer_cast(d_isolated_bmap_);

    // Source is isolated
    if (t_isolated_bmap[source / 8] & (1 << (source % 8))) {
        CUDA_CHECK(cudaEventRecord(stop_event, 0));
        CUDA_CHECK(cudaEventSynchronize(stop_event));
        CUDA_CHECK(
            cudaEventElapsedTime(&elapsed_time_, start_event, stop_event));

        return;
    }

    d_cub_temp_ = nullptr;

    if (sort_frontier_) {
        // This just gets the size. Pointers are dummy
        cub::DeviceRadixSort::SortKeys(
            d_cub_temp_,
            cub_alloc_size_,
            static_cast<const Value*>(d_frontier_),
            static_cast<Value*>(d_scratch_),
            (int)num_vertices_);
        CUDA_CHECK(cudaMalloc(&d_cub_temp_, cub_alloc_size_));
    }

    // Add src to frontier
    Value* d_next_nf_ptr;

    CUDA_CHECK(cudaMalloc(
        &d_next_nf_ptr,
        sizeof(Value) < sizeof(int) ? sizeof(int) : sizeof(Value)));
    thrust::device_ptr<Value> t_next_nf_ptr =
        thrust::device_pointer_cast(d_next_nf_ptr);
    *t_next_nf_ptr = 0;

    t_frontier[0] = source;
    Value nf = 1;
    Value front_start_idx = 0;

    while (nf) {
        // Number of blocks that we need
        size_t total_degree;
        fill_front_deg_exsum<Value, Degree, Edge>(
            static_cast<const Value*>(d_frontier_) + front_start_idx,
            nf,
            total_degree);
        size_t part_size = TOP_DOWN_EXPAND_DIMX * VALS_PER_THREAD;
        size_t total_blocks_req = (total_degree + part_size - 1) / part_size;

        thrust::counting_iterator<Edge> cnt_iter(0);
        thrust::device_ptr<Value> t_binsearch_output =
            thrust::device_pointer_cast(d_binsearch_output_);

        thrust::upper_bound(
            thrust::device,
            t_front_deg_exsum,
            t_front_deg_exsum + nf,
            thrust::make_transform_iterator(
                cnt_iter, scale_functor<Edge>(part_size)),
            thrust::make_transform_iterator(
                cnt_iter + total_blocks_req, scale_functor<Edge>(part_size)),
            t_binsearch_output);

        // Call advance kernel
        int grid_dim = std::min(max_grid_size_, total_blocks_req);

        level_advance_lb<
            kSkipQuantum,
            kForwardQuantum,
            Value,
            Edge,
            SkipValue,
            Degree,
            Offset><<<grid_dim, TOP_DOWN_EXPAND_DIMX>>>(
            static_cast<const Offset*>(d_offsets_),
            static_cast<const SkipValue*>(d_data_),
            static_cast<const Degree*>(d_degree_),
            d_num_lower_bits_,
            d_isolated_bmap_,
            static_cast<const Value*>(d_frontier_) + front_start_idx,
            nf,
            static_cast<const Edge*>(d_front_deg_exsum_),
            total_degree,
            static_cast<const Value*>(d_binsearch_output_),
            level_num++,
            sort_frontier_
                ? static_cast<Value*>(d_scratch_)
                : static_cast<Value*>(d_frontier_) + front_start_idx + nf,
            d_next_nf_ptr,
            static_cast<Value*>(d_distances_),
            reinterpret_cast<int*>(d_visited_bmap_));

        Value next_nf = (int)*t_next_nf_ptr;
        // Read scratch, sort, write back to frontier
        if (sort_frontier_) {
            int start_bit = static_cast<int>(0.35 * num_vertex_bits_);
            cub::DeviceRadixSort::SortKeys(
                d_cub_temp_,
                cub_alloc_size_,
                static_cast<const Value*>(d_scratch_),
                static_cast<Value*>(d_frontier_) + front_start_idx + nf,
                next_nf,
                start_bit,
                num_vertex_bits_);
        }

        front_start_idx += nf;
        nf = next_nf;
        *t_next_nf_ptr = 0;
    }

    CUDA_CHECK(cudaFree(d_next_nf_ptr));

    if (d_cub_temp_ != nullptr) {
        CUDA_CHECK(cudaFree(d_cub_temp_));
    }

    // End Profiling of CUDA section
    CUDA_CHECK(cudaEventRecord(stop_event, 0));
    CUDA_CHECK(cudaEventSynchronize(stop_event));
    CUDA_CHECK(cudaEventElapsedTime(&elapsed_time_, start_event, stop_event));

    std::vector<Value> temp_distances(num_vertices_);
    thrust::copy(
        t_distances, t_distances + num_vertices_, temp_distances.data());

#pragma omp parallel for
    for (size_t i = 0; i < num_vertices_; i++) {
        if (temp_distances[i] != std::numeric_limits<Value>::max())
            h_distances[i] = temp_distances[i];
        else
            h_distances[i] = std::numeric_limits<size_t>::max();
    }
}
