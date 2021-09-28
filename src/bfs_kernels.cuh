#pragma once
#include <cub/cub.cuh>

#include "byte_select.cuh"
#include "cuda_util.cuh"

#define TOP_DOWN_EXPAND_DIMX 128
#define VALS_PER_THREAD 5
#define PART_SIZE (TOP_DOWN_EXPAND_DIMX * VALS_PER_THREAD)
#define BYTE_FACTOR 2
#define INT_SIZE 32
#define MAX_BLOCKS 65535

template <typename Value>
__device__ __forceinline__ Value get_lower_value(
    const uint8_t* byte_pos,
    uint8_t bit_pos,
    uint8_t num_lower_bits);

template <>
__device__ __forceinline__ uint8_t get_lower_value<uint8_t>(
    const uint8_t* byte_pos,
    uint8_t bit_pos,
    uint8_t num_lower_bits) {
    uint8_t ret;

    uint16_t val = static_cast<uint16_t>(byte_pos[0]) |
                   (static_cast<uint16_t>(byte_pos[1]) << 8);
    ret = cub::BFE(val, bit_pos, num_lower_bits);

    return ret;
}

template <>
__device__ __forceinline__ uint16_t get_lower_value<uint16_t>(
    const uint8_t* byte_pos,
    uint8_t bit_pos,
    uint8_t num_lower_bits) {
    uint16_t ret;
    const uint16_t* aligned_ptr = reinterpret_cast<const uint16_t*>(
        (uintptr_t)byte_pos & 0xfffffffffffffffe);
    uint32_t val = static_cast<uint32_t>(aligned_ptr[0]) |
                   (static_cast<uint32_t>(aligned_ptr[1]) << 16);
    unsigned start_bit_pos = ((uintptr_t)(byte_pos) % 2) * 8 + bit_pos;
    ret = cub::BFE(val, start_bit_pos, num_lower_bits);
    return ret;
}

template <>
__device__ __forceinline__ uint32_t get_lower_value<uint32_t>(
    const uint8_t* byte_pos,
    uint8_t bit_pos,
    uint8_t num_lower_bits) {
    uint32_t ret;
    const uint32_t* aligned_ptr = reinterpret_cast<const uint32_t*>(
        (uintptr_t)byte_pos & 0xfffffffffffffffc);
    uint64_t val = static_cast<uint64_t>(aligned_ptr[0]) |
                   (static_cast<uint64_t>(aligned_ptr[1]) << 32);
    unsigned start_bit_pos = ((uintptr_t)(byte_pos) % 4) * 8 + bit_pos;
    ret = cub::BFE(val, start_bit_pos, num_lower_bits);
    return ret;
}

template <>
__device__ __forceinline__ uint64_t get_lower_value<uint64_t>(
    const uint8_t* byte_pos,
    uint8_t bit_pos,
    uint8_t num_lower_bits) {
    uint64_t ret;
    const uint64_t* aligned_ptr = reinterpret_cast<const uint64_t*>(
        (uintptr_t)byte_pos & 0xfffffffffffffff8);
    unsigned start_bit_pos = ((uintptr_t)(byte_pos) % 8) * 8 + bit_pos;
    unsigned bits_to_read = min(64 - start_bit_pos, (int)num_lower_bits);
    ret = cub::BFE(*aligned_ptr, start_bit_pos, bits_to_read);
    num_lower_bits -= bits_to_read;
    ret |= (cub::BFE(aligned_ptr[1], 0, num_lower_bits) << bits_to_read);

    return ret;
}

template <typename ValType, typename IndexType>
__device__ __forceinline__ IndexType binsearch_maxle(
    const ValType* vec,
    const ValType val,
    IndexType low,
    IndexType high) {
    while (true) {
        if (low == high) return low;  // we know it exists
        if ((low + 1) == high) return (vec[high] <= val) ? high : low;

        IndexType mid = low + (high - low) / 2;

        if (vec[mid] > val)
            high = mid - 1;
        else
            low = mid;
    }
}

template <typename Value, typename Degree>
struct fill_isolated_functor {
    thrust::device_ptr<uint8_t> bmap_;
    thrust::device_ptr<Degree> degree_;
    const Value N_;

    fill_isolated_functor(
        thrust::device_ptr<uint8_t> bmap,
        thrust::device_ptr<Degree> degree,
        Value N)
        : bmap_(bmap), degree_(degree), N_(N) {}

    __device__ void operator()(const Value& idx) {
        Value vid = idx * 8;
        uint8_t mask = 0;

#pragma unroll
        for (uint8_t i = 0; i < 8; i++, vid++) {
            uint8_t tmp = (vid < N_) ? (!degree_[vid] ? 1 : 0) : 0;
            mask |= (tmp << i);
        }

        bmap_[idx] = mask;
    }
};

template <typename Value, typename Degree, typename Edge>
struct fill_degree_functor {
    thrust::device_ptr<Value> frontier_;
    thrust::device_ptr<Degree> degree_;
    thrust::device_ptr<Edge> front_deg_exsum_;

    fill_degree_functor(
        thrust::device_ptr<Value> frontier,
        thrust::device_ptr<Degree> degree,
        thrust::device_ptr<Edge> front_deg_exsum)
        : frontier_(frontier),
          degree_(degree),
          front_deg_exsum_(front_deg_exsum) {}

    __device__ __forceinline__ void operator()(const Value& idx) {
        auto deg = degree_[frontier_[idx]];
        front_deg_exsum_[idx] = deg;
    }
};

template <typename Edge>
struct scale_functor {
    Edge scale_;
    scale_functor(Edge s) : scale_(s) {}

    __device__ __forceinline__ Edge operator()(const Edge& in) {
        return scale_ * in;
    }
};

struct seg_scan_functor {
    __host__ __device__ __forceinline__ uint32_t
    operator()(const uint32_t a, const uint32_t b) const {
        // MSB is the flag bit
        // If b's MSB is 1, return b, else return a + b (which also does an OR
        // over the flag)
        return a + b - a * (b >> 31);
    }
};

// Try to do better load balancing and reduce reg usage
template <
    size_t kSkipQuantum,
    size_t kForwardQuantum,
    typename Value,
    typename Edge,
    typename SkipValue,
    typename Degree,
    typename Offset>
__device__ void process_lists_in_block_lb_reg(
    const Offset* __restrict__ offsets,
    const SkipValue* __restrict__ data,
    const Degree* __restrict__ degrees,
    const uint8_t* __restrict__ num_lower_bits_vec,
    const uint8_t* __restrict__ isolated_bmap,
    const Value* __restrict__ curr_frontier,  // offset by block_first_list_idx
                                              // by caller
    const Value curr_level,
    Value* __restrict__ next_frontier,
    Value* __restrict__ next_nf_ptr,
    Value* __restrict__ distances,
    int* __restrict__ visited_bmap,
    const unsigned num_lists_in_block,
    const size_t first_idx_in_first_list,
    const size_t last_idx_in_last_list) {
    __shared__ const uint8_t* shared_upper[TOP_DOWN_EXPAND_DIMX];
    __shared__ const uint8_t* shared_lower[TOP_DOWN_EXPAND_DIMX];
    __shared__ size_t num_bytes_exsum[TOP_DOWN_EXPAND_DIMX];
    __shared__ uint8_t shared_num_lower_bits[TOP_DOWN_EXPAND_DIMX];
    __shared__ Degree shared_degree[TOP_DOWN_EXPAND_DIMX];
    __shared__ Value shared_candidates[TOP_DOWN_EXPAND_DIMX * VALS_PER_THREAD];

    __shared__ uint8_t shared_first_local_idx[TOP_DOWN_EXPAND_DIMX];
    __shared__ uint8_t shared_byte[TOP_DOWN_EXPAND_DIMX];
    __shared__ uint16_t shared_vals_per_thread_ex_sum[TOP_DOWN_EXPAND_DIMX];
    __shared__ uint16_t shared_bsearch_idx[TOP_DOWN_EXPAND_DIMX];
    __shared__ uint32_t shared_p_n_f_exsum[TOP_DOWN_EXPAND_DIMX];

    // Add these many bits during select(i) for first thread
    __shared__ size_t t0_common_offset;
    // select(i) becomes select(i-subtract_val) for first thread
    __shared__ size_t t0_subtract_select_val;
    // Current list operated by t0
    __shared__ uint16_t t0_list_idx;
    // For first list and first byte, mask can be different
    __shared__ uint8_t mask;
    // idx in shared candidates array
    __shared__ uint32_t shared_cand_idx;
    // idx in next frontier
    __shared__ Value global_offset;

    typedef cub::BlockScan<size_t, TOP_DOWN_EXPAND_DIMX> BlockScan_size_t;
    typedef cub::BlockScan<uint16_t, TOP_DOWN_EXPAND_DIMX> BlockScan_uint16_t;
    typedef cub::BlockScan<uint32_t, TOP_DOWN_EXPAND_DIMX> BlockScan_uint32_t;
    typedef cub::BlockReduce<int, TOP_DOWN_EXPAND_DIMX> BlockReduce_int;

    __shared__ union {
        typename BlockScan_size_t::TempStorage scan_size_t;
        typename BlockScan_uint16_t::TempStorage scan_uint16_t;
        typename BlockScan_uint32_t::TempStorage scan_uint32_t;
    } temp_storage;

    // We can do TOP_DOWN_EXPAND_DIXM lists in one iter
    const unsigned num_list_iters =
        (num_lists_in_block + TOP_DOWN_EXPAND_DIMX - 1) / TOP_DOWN_EXPAND_DIMX;

    for (unsigned list_iter = 0; list_iter < num_list_iters; list_iter++) {
        // Needed so that we don't overwrite t0 shared variables,
        // num_bytes_exsum, etc.
        if (list_iter) __syncthreads();

        unsigned local_list_idx =
            list_iter * TOP_DOWN_EXPAND_DIMX + threadIdx.x;

        if (!threadIdx.x) {
            t0_common_offset = 0;
            t0_subtract_select_val = 0;
            t0_list_idx = 0;
            mask = UINT8_MAX;

            if (!list_iter) shared_cand_idx = 0;
        }

        size_t num_upper_bytes = 0;
        unsigned num_valid_lists;

        if (list_iter != num_list_iters - 1) {
            num_valid_lists = TOP_DOWN_EXPAND_DIMX;
        } else {
            num_valid_lists = (num_lists_in_block % TOP_DOWN_EXPAND_DIMX)
                                  ? (num_lists_in_block % TOP_DOWN_EXPAND_DIMX)
                                  : TOP_DOWN_EXPAND_DIMX;
        }

        if (local_list_idx < num_lists_in_block) {
            const uint8_t* __restrict__ upper;

            auto vid = curr_frontier[/*block_first_list_idx +*/ local_list_idx];

            auto ef_start_ptr = data + offsets[vid];

            const SkipValue* __restrict__ forward =
                reinterpret_cast<const SkipValue*>(ef_start_ptr);
            Degree degree = degrees[vid];
            shared_degree[threadIdx.x] = degree;

            const Degree num_fwd_vals =
                kForwardQuantum ? degree / kForwardQuantum : 0;

            const uint8_t num_lower_bits = num_lower_bits_vec[vid];
            shared_num_lower_bits[threadIdx.x] = num_lower_bits;

            const size_t num_lower_bytes = (num_lower_bits * degree + 7) / 8;

            const uint8_t* __restrict__ lower =
                reinterpret_cast<const uint8_t*>(&forward[num_fwd_vals]);
            shared_lower[threadIdx.x] = lower;

            upper = &lower[num_lower_bytes];
            shared_upper[threadIdx.x] = upper;

            auto ef_end_ptr = data + offsets[vid + 1];
            // size of the upper array in bytes. This extends till the
            // beginning of next list.
            auto next_beg = reinterpret_cast<const uint8_t*>(ef_end_ptr);

            const size_t upper_size = next_beg - upper;
            num_upper_bytes = upper_size;

            // First list and first thread
            if (!local_list_idx) {
                auto first_select_val = first_idx_in_first_list + 1;

                if (kForwardQuantum && first_select_val >= kForwardQuantum) {
                    auto num_quantum = (first_select_val) / kForwardQuantum;
                    // fwd value is no. of zeroes up to num_quantum
                    auto fwd_val = forward[num_quantum - 1];
                    // subtract one bit if perfect division
                    auto sub_one = !(first_select_val % kForwardQuantum);
                    // These bytes can be skipped
                    auto delta =
                        (fwd_val + (num_quantum * kForwardQuantum) - sub_one) /
                        8;
                    num_upper_bytes -= delta;
                    shared_upper[threadIdx.x] += delta;

                    // Don't subtract self
                    t0_subtract_select_val =
                        (num_quantum * kForwardQuantum - sub_one);
                    // mask out the bits in the beginning
                    mask =
                        ~((uint8_t(1)
                           << ((fwd_val + (num_quantum * kForwardQuantum) -
                                sub_one) %
                               8)) -
                          1);
                    // Add these many bits during select(i)
                    t0_common_offset = delta * 8;
                }
            }  // end of if first list

            if (local_list_idx == num_lists_in_block - 1) {
                if (kForwardQuantum) {
                    auto last_select_val = last_idx_in_last_list + 1;
                    // Move end pos to the right of the last quantum
                    // unless it divides perfectly
                    auto sub_one = !(last_select_val % kForwardQuantum);
                    auto num_quantum =
                        ((last_select_val) / kForwardQuantum) + 1 - sub_one;

                    if (num_quantum <= degree / kForwardQuantum) {
                        auto fwd_val = forward[num_quantum - 1];
                        // IMPORTANT: Make sure it's byte aligned
                        auto delta =
                            (fwd_val + (num_quantum * kForwardQuantum) + 7) / 8;
                        num_upper_bytes -= (upper_size - delta);
                    }
                }
            }  // end of if last list

        }  // end of if valid list

        size_t total_bytes;

        BlockScan_size_t(temp_storage.scan_size_t)
            .ExclusiveSum(
                num_upper_bytes, num_bytes_exsum[threadIdx.x], total_bytes);

        // since num_bytes_exsum is shared and other shared structs earlier
        __syncthreads();

        size_t num_byte_iters =
            (total_bytes + TOP_DOWN_EXPAND_DIMX - 1) / (TOP_DOWN_EXPAND_DIMX);

        for (size_t byte_iter = 0; byte_iter < num_byte_iters; byte_iter++) {
            // We have a sync at the end of the loop. So, this is safe
            shared_byte[threadIdx.x] = 0;

            // flag (1 bit), byte_count (15 bits), pop_count (16 bits)
            uint32_t p_n_f = 0;
            uint16_t bsearch_idx = UINT16_MAX;
            size_t byte_num = byte_iter * TOP_DOWN_EXPAND_DIMX + threadIdx.x;

            if (byte_num < total_bytes) {
                // local list id
                bsearch_idx = binsearch_maxle(
                    num_bytes_exsum, byte_num, 0u, (num_valid_lists - 1));

                size_t byte_num_in_list =
                    byte_num - num_bytes_exsum[bsearch_idx];

                uint8_t byte = *(shared_upper[bsearch_idx] + byte_num_in_list);

                // If it's the first global list and first byte iter, we'll get
                // the mask
                if (!byte_iter && !threadIdx.x) byte &= mask;

                // set flag for is_start
                p_n_f |= ((!byte_num_in_list) << 31);
                // byte_count = 1
                p_n_f |= (1 << 16);

                uint8_t local_popc = __popc(byte);
                p_n_f |= local_popc;

                // end of valid bytes

                shared_byte[threadIdx.x] = byte;
            }

            // implies sync
            BlockScan_uint32_t(temp_storage.scan_uint32_t)
                .InclusiveScan(
                    p_n_f, shared_p_n_f_exsum[threadIdx.x], seg_scan_functor());

            uint16_t vals_per_thread = 0;

            shared_first_local_idx[threadIdx.x] = 0;
            shared_bsearch_idx[threadIdx.x] = bsearch_idx;

            if (bsearch_idx != UINT16_MAX) {
                // redefined for this scope

                unsigned local_list_idx =
                    list_iter * TOP_DOWN_EXPAND_DIMX + bsearch_idx;

                size_t first_select_val = 1;
                size_t last_select_val = shared_degree[bsearch_idx];

                if (!local_list_idx)
                    first_select_val = first_idx_in_first_list + 1;

                if (local_list_idx == num_lists_in_block - 1)
                    last_select_val = last_idx_in_last_list + 1;

                size_t subtract_select_val = 0;

                if (bsearch_idx == t0_list_idx) {
                    subtract_select_val = t0_subtract_select_val;
                }

                uint32_t p_n_f = shared_p_n_f_exsum[threadIdx.x];
                uint8_t byte = shared_byte[threadIdx.x];
                uint8_t local_popc = __popc(byte);
                // Only care about lower 16 bits for popc
                uint16_t local_popc_exsum = (p_n_f & 0xFFFF) - local_popc;
                int64_t before_sum = subtract_select_val + local_popc_exsum;
                // Inclusive
                int64_t first_local_idx = 0;
                int64_t last_local_idx = local_popc - 1;

                first_local_idx +=
                    max((int64_t)0, (int64_t)(first_select_val)-before_sum - 1);
                last_local_idx -=
                    max((int64_t)0,
                        before_sum + local_popc - (int64_t)last_select_val);

                // Will be less than 8
                shared_first_local_idx[threadIdx.x] = first_local_idx;
                vals_per_thread =
                    max((int64_t)0, last_local_idx - first_local_idx + 1);
            }

            // reuse temp storage
            __syncthreads();

            uint16_t total_values;

            BlockScan_uint16_t(temp_storage.scan_uint16_t)
                .ExclusiveSum(
                    vals_per_thread,
                    shared_vals_per_thread_ex_sum[threadIdx.x],
                    total_values);

            // This can be at most 8 since each byte can have max 8 bits set
            uint16_t vals_iters = (total_values + TOP_DOWN_EXPAND_DIMX - 1) /
                                  TOP_DOWN_EXPAND_DIMX;

            // sync shared_vals_per_thread_ex_sum
            __syncthreads();

            for (auto w = 0; w < vals_iters; w++) {
                uint16_t val_idx = w * TOP_DOWN_EXPAND_DIMX + threadIdx.x;

                if (val_idx < total_values) {
                    uint16_t val_orig_tid = binsearch_maxle(
                        shared_vals_per_thread_ex_sum,
                        val_idx,
                        0,
                        TOP_DOWN_EXPAND_DIMX - 1);

                    uint16_t val_in_list =
                        val_idx - shared_vals_per_thread_ex_sum[val_orig_tid];
                    uint16_t bsearch_idx = shared_bsearch_idx[val_orig_tid];
                    uint8_t byte = shared_byte[val_orig_tid];
                    uint32_t p_n_f = shared_p_n_f_exsum[val_orig_tid];
                    uint8_t local_popc = __popc(byte);
                    // Only care about lower 16 bits for popc
                    uint16_t local_popc_exsum = (p_n_f & 0xFFFF) - local_popc;
                    // Right shift by 16 and extract 15 bits
                    uint16_t bytes_before_me = cub::BFE(p_n_f, 16, 15) - 1;
                    uint16_t popc_iter =
                        shared_first_local_idx[val_orig_tid] + val_in_list;

                    uint8_t num_lower_bits = shared_num_lower_bits[bsearch_idx];
                    bool is_t0_list = (bsearch_idx == t0_list_idx);
                    size_t subtract_select_val =
                        is_t0_list * t0_subtract_select_val;
                    size_t common_offset = is_t0_list * t0_common_offset;

                    const size_t before_sum =
                        subtract_select_val + local_popc_exsum;

                    size_t destination_idx = before_sum + popc_iter;

                    Value upper_val = common_offset + bytes_before_me * 8 +
                                      dSelectInByte[byte][popc_iter] -
                                      destination_idx;

                    const size_t pos = (destination_idx)*num_lower_bits;

                    const uint8_t* __restrict__ ptr =
                        shared_lower[bsearch_idx] + (pos / 8);

                    Value lower_val =
                        get_lower_value<Value>(ptr, pos % 8, num_lower_bits);
                    const Value final_val =
                        (upper_val << num_lower_bits) | lower_val;

                    // Test and test and set pattern
                    bool was_visited = (visited_bmap[final_val / INT_SIZE] >>
                                        (final_val % INT_SIZE)) &
                                       1;

                    // Add to candidates
                    bool is_isolated =
                        (isolated_bmap[final_val / 8] >> (final_val % 8)) & 1;

                    if (!was_visited) {
                        distances[final_val] = curr_level + 1;

                        if (is_isolated) {
                            int new_val = 1 << (final_val % INT_SIZE);
                            atomicOr(
                                &visited_bmap[final_val / INT_SIZE], new_val);
                        } else {
                            int new_val = 1 << (final_val % INT_SIZE);
                            int old_val = atomicOr(
                                &visited_bmap[final_val / INT_SIZE], new_val);
                            bool atomic_was_visited =
                                (old_val >> (final_val % INT_SIZE)) & 1;
                            if (!atomic_was_visited) {
                                auto old_idx = atomicAdd(&shared_cand_idx, 1);
                                shared_candidates[old_idx] = final_val;
                            }
                        }
                    }

                }  // end of if cond

            }  // end of vals loop

            if (byte_iter < num_byte_iters - 1) {
                // For updating t0
                __syncthreads();

                // last thread
                // we only care for these values if it's not the last iteration
                if (threadIdx.x == TOP_DOWN_EXPAND_DIMX - 1) {
                    if (shared_bsearch_idx[threadIdx.x] == t0_list_idx) {
                        // Same list continues to next iter
                        uint32_t p_n_f = shared_p_n_f_exsum[threadIdx.x];
                        uint16_t bytes_before_me = cub::BFE(p_n_f, 16, 15) - 1;

                        // Add to subtract_select_val and common_offset
                        t0_subtract_select_val += (p_n_f & 0xFFFF);
                        t0_common_offset += (bytes_before_me + 1) * 8;
                    } else {
                        // This list becomes t0's list in next iter
                        t0_list_idx = shared_bsearch_idx[threadIdx.x];
                        uint32_t p_n_f = shared_p_n_f_exsum[threadIdx.x];
                        uint16_t bytes_before_me = cub::BFE(p_n_f, 16, 15) - 1;

                        // Set subtract_select_val and common_offset
                        t0_subtract_select_val = (p_n_f & 0xFFFF);
                        t0_common_offset = (bytes_before_me + 1) * 8;
                    }

                }  // end of last thread

                // For next iter
                __syncthreads();
            }

        }  // end of byte iter

    }  // end of list iters

    // To use shared_cand_idx
    __syncthreads();

    if (!threadIdx.x) {
        global_offset =
            util::atomicAdd(next_nf_ptr, static_cast<Value>(shared_cand_idx));
    }

    // To use global_offset
    __syncthreads();

    unsigned cand_iters =
        (shared_cand_idx + TOP_DOWN_EXPAND_DIMX - 1) / TOP_DOWN_EXPAND_DIMX;

    for (unsigned i = 0; i < cand_iters; i++) {
        auto idx = i * TOP_DOWN_EXPAND_DIMX + threadIdx.x;
        if (idx < shared_cand_idx) {
            next_frontier[global_offset + idx] = shared_candidates[idx];
        }
    }

    // For next invocation
    __syncthreads();
}

template <
    size_t kSkipQuantum,
    size_t kForwardQuantum,
    typename Value,
    typename Edge,
    typename SkipValue,
    typename Degree,
    typename Offset>
__global__ void __launch_bounds__(TOP_DOWN_EXPAND_DIMX) level_advance_lb(
    const Offset* __restrict__ offsets,
    const SkipValue* __restrict__ data,
    const Degree* __restrict__ degrees,
    const uint8_t* __restrict__ num_lower_bits_vec,
    const uint8_t* __restrict__ isolated_bmap,
    const Value* __restrict__ curr_frontier,
    const Value nf,
    const Edge* __restrict__ degree_exsum,
    const size_t total_degree,
    const Value* __restrict__ work_positions,
    const Value curr_level,
    Value* __restrict__ next_frontier,
    Value* __restrict__ next_nf_ptr,
    Value* __restrict__ distances,
    int* __restrict__ visited_bmap) {
    static_assert(
        TOP_DOWN_EXPAND_DIMX * BYTE_FACTOR * 8 <=
        std::numeric_limits<uint16_t>::max());
    static_assert(
        VALS_PER_THREAD * TOP_DOWN_EXPAND_DIMX <=
        std::numeric_limits<uint16_t>::max());
    static_assert(sizeof(Degree) <= sizeof(Edge));
    static_assert(sizeof(Degree) <= sizeof(SkipValue));

    size_t num_block_iters =
        (total_degree + gridDim.x * TOP_DOWN_EXPAND_DIMX * VALS_PER_THREAD -
         1) /
        (gridDim.x * TOP_DOWN_EXPAND_DIMX * VALS_PER_THREAD);

    for (size_t block_iter = 0; block_iter < num_block_iters; block_iter++) {
        size_t eff_block_id = gridDim.x * block_iter + blockIdx.x;
        size_t block_first_elem_idx =
            eff_block_id * TOP_DOWN_EXPAND_DIMX * VALS_PER_THREAD;

        if (block_first_elem_idx >= total_degree) break;

        size_t block_last_elem_idx = min(
            total_degree - 1,
            (eff_block_id + 1) * TOP_DOWN_EXPAND_DIMX * VALS_PER_THREAD - 1);

        size_t block_first_list_idx, block_last_list_idx;

        // -1 because thrust returns the upper bound
        block_first_list_idx = work_positions[eff_block_id] - 1;

        // there is one block after us
        if (block_last_elem_idx < total_degree - 1) {
            // Next block's first list
            // -1 due to thrust upper bound
            block_last_list_idx = work_positions[eff_block_id + 1] - 1;

            // If next block's start position perfectly aligns to the start
            // of a list, we need to move back one idx to get the previous list
            if (degree_exsum[block_last_list_idx] == block_last_elem_idx + 1)
                block_last_list_idx--;
        } else {
            // This is the last block
            block_last_list_idx = nf - 1;
        }

        // Find start position in first list
        size_t first_idx_in_first_list =
            block_first_elem_idx - degree_exsum[block_first_list_idx];

        // End position in last list
        size_t last_idx_in_last_list =
            block_last_elem_idx - degree_exsum[block_last_list_idx];

        // In this block_iter
        unsigned num_lists_in_block =
            block_last_list_idx - block_first_list_idx + 1;

        process_lists_in_block_lb_reg<
            kSkipQuantum,
            kForwardQuantum,
            Value,
            Edge,
            SkipValue,
            Degree,
            Offset>(
            offsets,
            data,
            degrees,
            num_lower_bits_vec,
            isolated_bmap,
            curr_frontier + block_first_list_idx,
            curr_level,
            next_frontier,
            next_nf_ptr,
            distances,
            visited_bmap,
            num_lists_in_block,
            first_idx_in_first_list,
            last_idx_in_last_list);

    }  // end of block iter
}
