#pragma once
#include <folly/experimental/EliasFanoCoding.h>

#include <iostream>

#include "csr.h"
#include "ef_param.h"
#include "util.h"

#define GET_CHUNK_SIZE(V, S, ...) get_num_chunks_vec<V, S>(__VA_ARGS__)

template <size_t kSkipQuantum, size_t kForwardQuantum>
class EFGraph;

template <size_t kSkipQuantum, size_t kForwardQuantum>
class EFLayout {
    const CSR& csr_;
    size_t num_vertices_, num_edges_;
    std::vector<size_t> chunk_off_exsum_;
    ef_param_t ef_param_;
    size_t offset_size_, data_size_, num_lower_bits_size_, degree_size_,
        storage_size_;

    void set_ef_params();

    template <typename Value, typename SkipValue>
    size_t get_nbr_list_size(uint64_t vid) const;

    template <typename Value, typename SkipValue>
    void get_num_chunks_vec(
        std::vector<size_t>& num_chunks_vec,
        uint8_t chunk_align_size) const;

    friend class EFGraph<kSkipQuantum, kForwardQuantum>;

public:
    EFLayout(const CSR& csr)
        : csr_(csr),
          num_vertices_(csr_.get_num_vertices()),
          num_edges_(csr_.get_num_edges()) {
        set_ef_params();
    }

    ef_param_t get_ef_params() const {
        return ef_param_;
    }

    size_t get_storage_size() const {
        return storage_size_;
    }
};

// Get vid's neighbour list's size when encoded with EF
template <size_t kSkipQuantum, size_t kForwardQuantum>
template <typename Value, typename SkipValue>
size_t EFLayout<kSkipQuantum, kForwardQuantum>::get_nbr_list_size(
    uint64_t vid) const {
    using namespace folly::compression;
    typedef EliasFanoEncoderV2<Value, SkipValue, kSkipQuantum, kForwardQuantum>
        Encoder;

    size_t c_size = 0;
    auto it_pair = csr_.get_nbrs(vid);
    auto start = it_pair.first;
    auto end = it_pair.second;

    if (start != end) {
        c_size = Encoder::Layout::fromUpperBoundAndSize(
                     static_cast<Value>(*(end - 1)),
                     static_cast<size_t>(end - start))
                     .bytes();
    }

    return c_size;
}

template <size_t kSkipQuantum, size_t kForwardQuantum>
template <typename Value, typename SkipValue>
void EFLayout<kSkipQuantum, kForwardQuantum>::get_num_chunks_vec(
    std::vector<size_t>& num_chunks_vec,
    uint8_t chunk_align_size) const {
    assert(num_chunks_vec.size() == num_vertices_);

#pragma omp parallel for
    for (size_t i = 0; i < num_chunks_vec.size(); i++) {
        size_t size = get_nbr_list_size<Value, SkipValue>(i);
        num_chunks_vec[i] = (size + chunk_align_size - 1) / chunk_align_size;
    }
}

template <size_t kSkipQuantum, size_t kForwardQuantum>
void EFLayout<kSkipQuantum, kForwardQuantum>::set_ef_params() {
    uint8_t val_type_size, edge_type_size, fwd_type_size, degree_type_size,
        chunk_align_size, chunk_offset_size;

    val_type_size = get_unsigned_type_size(num_vertices_);
    edge_type_size = get_unsigned_type_size(num_edges_);

    uint64_t max_degree = csr_.get_max_degree();
    degree_type_size = get_unsigned_type_size(max_degree);

    // Forward pointers store the number of zeros. Can be max 2n.
    // There are no forward pointers
    // if (!kForwardQuantum  || kForwardQuantum > max_degree + 1)
    // in which case fwd_type_size = sizeof(uint8_t),
    // but this is simpler and reduces compilation time since we need to
    // instantiate fewer things. fwd_type will be the same as the degree type
    // or one type larger than that. The common case is that we have forward
    // pointers.
    fwd_type_size = get_unsigned_type_size(max_degree * 2);

    // Right now chunks are aligned to forward values.
    // This can be changed later to remove alignment restrictions
    // However, that would require reading unaligned forward values in
    // CUDA code
    chunk_align_size = fwd_type_size;

    std::vector<size_t> num_chunks_vec(num_vertices_);

    // Get num_chunks for each neighbour list
    VS2_GEN_ARGS(
        val_type_size,
        fwd_type_size,
        GET_CHUNK_SIZE,
        num_chunks_vec,
        chunk_align_size);

    chunk_off_exsum_.resize(num_vertices_ + 1);

    chunk_off_exsum_[0] = 0;
    for (size_t i = 1; i < num_vertices_ + 1; i++) {
        chunk_off_exsum_[i] = chunk_off_exsum_[i - 1] + num_chunks_vec[i - 1];
    }

    size_t total_chunks = *chunk_off_exsum_.rbegin();

    chunk_offset_size = get_unsigned_type_size(total_chunks);

    offset_size_ = chunk_off_exsum_.size() * chunk_offset_size;
    data_size_ = total_chunks * chunk_align_size;
    degree_size_ = degree_type_size * num_vertices_;
    num_lower_bits_size_ = sizeof(uint8_t) * num_vertices_;

    storage_size_ =
        offset_size_ + data_size_ + degree_size_ + num_lower_bits_size_;

    ef_param_ = {val_type_size,
                 edge_type_size,
                 fwd_type_size,
                 degree_type_size,
                 chunk_align_size,
                 chunk_offset_size};
}
