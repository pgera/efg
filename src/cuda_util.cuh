#pragma once
#include <cuda.h>
#include <cuda_runtime_api.h>
#include <stdio.h>

// https://stackoverflow.com/a/14038590
#define CUDA_CHECK(ans) \
    { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(
    cudaError_t code,
    const char* file,
    int line,
    bool abort = true) {
    if (code != cudaSuccess) {
        fprintf(
            stderr,
            "GPUassert: %s %s %d\n",
            cudaGetErrorString(code),
            file,
            line);
        if (abort) exit(code);
    }
}

namespace util {

template <typename T, size_t n>
struct AtomicAddIntegerImpl;

// Code from Pytorch
template <typename T>
struct AtomicAddIntegerImpl<T, 1> {
    inline __device__ T operator()(T* address, T val) {
        size_t offset = (size_t)address & 3;
        uint32_t* address_as_ui = (uint32_t*)((char*)address - offset);
        uint32_t old = *address_as_ui;
        uint32_t shift = offset * 8;
        uint32_t old_byte;
        uint32_t newval;
        uint32_t assumed;

        do {
            assumed = old;
            old_byte = (old >> shift) & 0xff;
            // preserve size in initial cast. Casting directly to uint32_t pads
            // negative signed values with 1's (e.g. signed -1 = unsigned ~0).
            newval = static_cast<uint8_t>(val + old_byte);
            newval = (old & ~(0x000000ff << shift)) | (newval << shift);
            old = atomicCAS(address_as_ui, assumed, newval);
        } while (assumed != old);

        return old_byte;
    }
};

template <typename T>
struct AtomicAddIntegerImpl<T, 2> {
    inline __device__ T operator()(T* address, T val) {
        size_t offset = (size_t)address & 2;
        uint32_t* address_as_ui = (uint32_t*)((char*)address - offset);
        bool is_32_align = offset;
        uint32_t old = *address_as_ui;
        uint32_t old_bytes;
        uint32_t newval;
        uint32_t assumed;

        do {
            assumed = old;
            old_bytes = is_32_align ? old >> 16 : old & 0xffff;
            // preserve size in initial cast. Casting directly to uint32_t pads
            // negative signed values with 1's (e.g. signed -1 = unsigned ~0).
            newval = static_cast<uint16_t>(val + old_bytes);
            newval = is_32_align ? (old & 0xffff) | (newval << 16)
                                 : (old & 0xffff0000) | newval;
            old = atomicCAS(address_as_ui, assumed, newval);
        } while (assumed != old);

        return old_bytes;
    }
};

inline __device__ uint8_t atomicAdd(uint8_t* address, uint8_t val) {
    return AtomicAddIntegerImpl<uint8_t, sizeof(uint8_t)>()(address, val);
}

inline __device__ uint16_t atomicAdd(uint16_t* address, uint16_t val) {
    return AtomicAddIntegerImpl<uint16_t, sizeof(uint16_t)>()(address, val);
}

inline __device__ uint32_t atomicAdd(uint32_t* address, uint32_t val) {
    return ::atomicAdd(address, val);
}

inline __device__ uint64_t atomicAdd(uint64_t* address, uint64_t val) {
    static_assert(sizeof(uint64_t) == sizeof(unsigned long long));
    return ::atomicAdd((unsigned long long*)address, (unsigned long long)val);
}
}  // namespace util
