#pragma once

uint8_t get_unsigned_type_size(uint64_t val);
std::string get_sha_sum(void* data, size_t size);

// V is value type and S is skip type
#define V2_GEN_ARGS(V_size, S, func, ...)        \
    do {                                         \
        if (V_size == sizeof(uint8_t)) {         \
            func(uint8_t, S, __VA_ARGS__);       \
        } else if (V_size == sizeof(uint16_t)) { \
            func(uint16_t, S, __VA_ARGS__);      \
        } else if (V_size == sizeof(uint32_t)) { \
            func(uint32_t, S, __VA_ARGS__);      \
        } else if (V_size == sizeof(uint64_t)) { \
            func(uint64_t, S, __VA_ARGS__);      \
        } else {                                 \
            assert(0);                           \
        }                                        \
    } while (0)

// V is value type and S is skip type
#define V2_GEN(V_size, S, func)                  \
    do {                                         \
        if (V_size == sizeof(uint8_t)) {         \
            func(uint8_t, S);                    \
        } else if (V_size == sizeof(uint16_t)) { \
            func(uint16_t, S);                   \
        } else if (V_size == sizeof(uint32_t)) { \
            func(uint32_t, S);                   \
        } else if (V_size == sizeof(uint64_t)) { \
            func(uint64_t, S);                   \
        } else {                                 \
            assert(0);                           \
        }                                        \
    } while (0)

// V is value type and S is skip type
#define VS2_GEN_ARGS(V_size, S_size, func, ...)               \
    do {                                                      \
        if (S_size == sizeof(uint8_t)) {                      \
            V2_GEN_ARGS(V_size, uint8_t, func, __VA_ARGS__);  \
        } else if (S_size == sizeof(uint16_t)) {              \
            V2_GEN_ARGS(V_size, uint16_t, func, __VA_ARGS__); \
        } else if (S_size == sizeof(uint32_t)) {              \
            V2_GEN_ARGS(V_size, uint32_t, func, __VA_ARGS__); \
        } else if (S_size == sizeof(uint64_t)) {              \
            V2_GEN_ARGS(V_size, uint64_t, func, __VA_ARGS__); \
        } else {                                              \
            assert(0);                                        \
        }                                                     \
    } while (0)

// V is value type and S is skip type
#define VS2_GEN(V_size, S_size, func)            \
    do {                                         \
        if (S_size == sizeof(uint8_t)) {         \
            V2_GEN(V_size, uint8_t, func);       \
        } else if (S_size == sizeof(uint16_t)) { \
            V2_GEN(V_size, uint16_t, func);      \
        } else if (S_size == sizeof(uint32_t)) { \
            V2_GEN(V_size, uint32_t, func);      \
        } else if (S_size == sizeof(uint64_t)) { \
            V2_GEN(V_size, uint64_t, func);      \
        } else {                                 \
            assert(0);                           \
        }                                        \
    } while (0)
