#pragma once
#include <folly/experimental/Instructions.h>
#include <folly/experimental/Select64.h>

namespace EF {

template <typename Instructions>
uint64_t readLowerPart(
    const uint8_t* lower_,
    const size_t i,
    const size_t numLowerBits_) {
    const size_t pos = i * numLowerBits_;
    const uint8_t* ptr = lower_ + (pos / 8);
    const uint64_t ptrv = folly::loadUnaligned<uint64_t>(ptr);
    return Instructions::bzhi(ptrv >> (pos % 8), numLowerBits_);
}

// assume total size is multiple of 64 bits
// mask is for the first read in the region
// index is 1 based. 1 = first set bit and so on
// assume unaligned accesses are supported
// assume bytes at end are readable
template <typename Instructions>
uint64_t select(const uint8_t* upper, size_t index, uint64_t mask) {
    assert(index);

    const uint64_t* ptr = reinterpret_cast<const uint64_t*>(upper);
    // size_t num_words = (upper_size + sizeof(uint64_t) - 1)/sizeof(uint64_t);

    size_t n = index;
    size_t cnt;
    // Find necessary block.
    uint64_t val = (*ptr) & mask;
    while ((cnt = __builtin_popcountll(val)) < n) {
        n -= cnt;
        ptr += 1;
        val = *ptr;
    }

    // Search within word
    return (reinterpret_cast<const uint8_t*>(ptr) - upper) * 8 +
           folly::select64<Instructions>(val, n - 1);
}
}  // namespace EF
