#pragma once
#include "ef_layout.h"
#include "ef_util.h"

#define ENCODE_GRAPH(V, S) encode_graph<V, S>()

#define SANITY_HSW(V, S, rc) \
    sanity_check_impl<V, S, folly::compression::instructions::Haswell>(rc)
#define SANITY(V, S, rc) \
    sanity_check_impl<V, S, folly::compression::instructions::Default>(rc)

template <size_t kSkipQuantum, size_t kForwardQuantum>
class CUEFGraph;

template <size_t kSkipQuantum, size_t kForwardQuantum>
class EFGraph {
    const EFLayout<kSkipQuantum, kForwardQuantum>& ef_layout_;
    const ef_param_t ef_param_;
    size_t num_vertices_, num_edges_;
    std::vector<uint8_t> data_vec_;
    std::vector<uint8_t> num_lower_bits_vec_;
    std::vector<size_t> degree_vec_;

    template <typename Value, typename SkipValue>
    void encode_nbr_list(
        uint64_t vid,
        uint8_t& num_lower_bits,
        void* output,
        size_t max_size);

    template <typename Value, typename SkipValue>
    void encode_graph();

    template <typename Value, typename SkipValue, typename Instructions>
    void sanity_check_impl(bool& rc) const;

public:
    EFGraph(const EFLayout<kSkipQuantum, kForwardQuantum>& ef_layout)
        : ef_layout_(ef_layout),
          ef_param_(ef_layout_.ef_param_),
          num_vertices_(ef_layout_.num_vertices_),
          num_edges_(ef_layout_.num_edges_),
          data_vec_(((ef_layout_.data_size_ + 7) / 8) * 8, 0),
          num_lower_bits_vec_(num_vertices_, 0),
          degree_vec_(num_vertices_, 0) {
        VS2_GEN(ef_param_.val_type_size, ef_param_.fwd_type_size, ENCODE_GRAPH);

        auto csr = ef_layout_.csr_;
        #pragma omp parallel for
        for (size_t i = 0; i < num_vertices_; i++) {
            auto degree = csr.get_degree(i);
            degree_vec_[i] = degree;
        }
    }

    bool sanity_check() const {
        bool rc;
        if (folly::compression::instructions::detect() >=
            folly::compression::instructions::Type::HASWELL) {
            VS2_GEN_ARGS(
                ef_param_.val_type_size,
                ef_param_.fwd_type_size,
                SANITY_HSW,
                rc);
        } else {
            VS2_GEN_ARGS(
                ef_param_.val_type_size, ef_param_.fwd_type_size, SANITY, rc);
        }
        return rc;
    };

    ef_param_t get_ef_params() const {
        return ef_param_;
    }

    const std::vector<uint8_t>& view_data_vec() const {
        return data_vec_;
    }

    const std::vector<uint8_t>& view_num_lower_bits_vec() const {
        return num_lower_bits_vec_;
    }

    const std::vector<size_t>& view_offsets_vec() const {
        return ef_layout_.chunk_off_exsum_;
    }

    const std::vector<size_t>& view_degree_vec() const {
        return degree_vec_;
    }

    size_t get_num_vertices() const {
        return num_vertices_;
    }

    size_t get_num_edges() const {
        return num_edges_;
    }
};

template <size_t kSkipQuantum, size_t kForwardQuantum>
template <typename Value, typename SkipValue>
void EFGraph<kSkipQuantum, kForwardQuantum>::encode_graph() {
    const auto& chunk_off_exsum = ef_layout_.chunk_off_exsum_;
    const auto chunk_align_size = ef_layout_.ef_param_.chunk_align_size;

    #pragma omp parallel for
    for (size_t i = 0; i < num_vertices_; i++) {
        size_t output_size =
            (chunk_off_exsum[i + 1] - chunk_off_exsum[i]) * chunk_align_size;
        auto output_ptr =
            data_vec_.data() + chunk_off_exsum[i] * chunk_align_size;
        encode_nbr_list<Value, SkipValue>(
            i,
            num_lower_bits_vec_[i],
            static_cast<void*>(output_ptr),
            output_size);
    }
}

template <size_t kSkipQuantum, size_t kForwardQuantum>
template <typename Value, typename SkipValue>
void EFGraph<kSkipQuantum, kForwardQuantum>::encode_nbr_list(
    uint64_t vid,
    uint8_t& num_lower_bits,
    void* output,
    size_t max_size) {
    using namespace folly::compression;
    typedef EliasFanoEncoderV2<Value, SkipValue, kSkipQuantum, kForwardQuantum>
        Encoder;

    auto it_pair = ef_layout_.csr_.get_nbrs(vid);
    auto start = it_pair.first;
    auto end = it_pair.second;
    num_lower_bits = 0;

    if (start != end) {
        Encoder encoder(
            static_cast<size_t>(end - start), static_cast<Value>(*(end - 1)));
        while (start != end) {
            encoder.add(static_cast<Value>(*start));
            start++;
        }

        auto enc_list = encoder.finish();
        num_lower_bits = enc_list.numLowerBits;
        assert(enc_list.data.size() <= max_size);
        std::memcpy(
            output,
            static_cast<void*>(enc_list.data.data()),
            enc_list.data.size());
    }
}

template <size_t kSkipQuantum, size_t kForwardQuantum>
template <typename Value, typename SkipValue, typename Instructions>
void EFGraph<kSkipQuantum, kForwardQuantum>::sanity_check_impl(bool& rc) const {
    auto csr = ef_layout_.csr_;
    // Decompress the edge list and compare to csr's edge list
    std::vector<uint64_t> output_elist(num_edges_);

    #pragma omp parallel for
    for (size_t i = 0; i < num_vertices_; i++) {
        uint64_t* output = output_elist.data() + csr.get_degree_exsum(i);
        auto degree = csr.get_degree(i);

        auto ef_start_offset =
            ef_layout_.chunk_off_exsum_.at(i) * ef_param_.chunk_align_size;

        const size_t num_fwd_vals =
            kForwardQuantum ? degree / kForwardQuantum : 0;
        const size_t num_fwd_bytes = num_fwd_vals * sizeof(SkipValue);

        const size_t num_lower_bits = num_lower_bits_vec_.at(i);
        const size_t num_lower_bytes = (num_lower_bits * degree + 7) / 8;

        const SkipValue* fwd_addr = reinterpret_cast<const SkipValue*>(
            data_vec_.data() + ef_start_offset);

        const uint8_t* lower_addr = reinterpret_cast<const uint8_t*>(
            data_vec_.data() + ef_start_offset + num_fwd_bytes);

        #pragma omp parallel for
        for (uint64_t e = 0; e < degree; e++) {
            const uint8_t* upper_base_addr = static_cast<const uint8_t*>(
                data_vec_.data() + ef_start_offset + num_fwd_bytes +
                num_lower_bytes);

            uint64_t upper_part = 0, lower_part = 0;
            uint64_t mask = std::numeric_limits<uint64_t>::max();
            size_t select_val = e + 1;

            if (kForwardQuantum && select_val > kForwardQuantum) {
                // Get closest forward pointer
                size_t fwd_idx = (select_val - 1) / kForwardQuantum;
                // fwd value is no. of zeroes up to fwd_idx
                SkipValue fwd_val = fwd_addr[fwd_idx - 1];
                // Add no. of 1s
                size_t addr_delta = (fwd_val + (fwd_idx * kForwardQuantum)) / 8;
                upper_base_addr += addr_delta;
                select_val -= (fwd_idx * kForwardQuantum);
                mask =
                    ~((uint64_t(1)
                       << ((fwd_val + (fwd_idx * kForwardQuantum)) % 8)) -
                      1);
                upper_part += addr_delta * 8;
            }

            upper_part +=
                EF::select<Instructions>(upper_base_addr, select_val, mask) - e;

            lower_part =
                EF::readLowerPart<Instructions>(lower_addr, e, num_lower_bits);

            auto total = (upper_part << num_lower_bits) | lower_part;
            Value val = static_cast<Value>(total);
            output[e] = val;
        }
    }

    rc = (csr.get_elist() == output_elist);
}
