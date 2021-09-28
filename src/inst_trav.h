#pragma once
// This giant block was generated with a python script. It instantiates
// traverse_impl for the cross product of different types.
// TODO: There has to be a better way of doing this.
#define INSTANTIATE_TRAVERSE(                                          \
    v_size, deg_size, skip_size, e_size, chunk_offset_size, func, ...) \
    do {                                                               \
        if (v_size == sizeof(uint8_t)) {                               \
            if (deg_size == sizeof(uint8_t)) {                         \
                if (skip_size == sizeof(uint8_t)) {                    \
                    if (e_size == sizeof(uint8_t)) {                   \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint16_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint32_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint32_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint32_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint32_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint32_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
                if (skip_size == sizeof(uint16_t)) {                   \
                    if (e_size == sizeof(uint8_t)) {                   \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint16_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint32_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
            }                                                          \
            if (deg_size == sizeof(uint16_t)) {                        \
                if (skip_size == sizeof(uint16_t)) {                   \
                    if (e_size == sizeof(uint16_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint32_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
                if (skip_size == sizeof(uint32_t)) {                   \
                    if (e_size == sizeof(uint16_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint32_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
            }                                                          \
            if (deg_size == sizeof(uint32_t)) {                        \
                if (skip_size == sizeof(uint32_t)) {                   \
                    if (e_size == sizeof(uint32_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
                if (skip_size == sizeof(uint64_t)) {                   \
                    if (e_size == sizeof(uint32_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
            }                                                          \
            if (deg_size == sizeof(uint64_t)) {                        \
                if (skip_size == sizeof(uint64_t)) {                   \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint8_t,                               \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
            }                                                          \
        }                                                              \
                                                                       \
        if (v_size == sizeof(uint16_t)) {                              \
            if (deg_size == sizeof(uint8_t)) {                         \
                if (skip_size == sizeof(uint8_t)) {                    \
                    if (e_size == sizeof(uint8_t)) {                   \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint16_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint32_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
                if (skip_size == sizeof(uint16_t)) {                   \
                    if (e_size == sizeof(uint8_t)) {                   \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint16_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint32_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
            }                                                          \
                                                                       \
            if (deg_size == sizeof(uint16_t)) {                        \
                if (skip_size == sizeof(uint16_t)) {                   \
                    if (e_size == sizeof(uint16_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint32_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
                if (skip_size == sizeof(uint32_t)) {                   \
                    if (e_size == sizeof(uint16_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint32_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
            }                                                          \
                                                                       \
            if (deg_size == sizeof(uint32_t)) {                        \
                if (skip_size == sizeof(uint32_t)) {                   \
                    if (e_size == sizeof(uint32_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
                if (skip_size == sizeof(uint64_t)) {                   \
                    if (e_size == sizeof(uint32_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
            }                                                          \
            if (deg_size == sizeof(uint64_t)) {                        \
                if (skip_size == sizeof(uint64_t)) {                   \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint16_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
            }                                                          \
        }                                                              \
                                                                       \
        if (v_size == sizeof(uint32_t)) {                              \
            if (deg_size == sizeof(uint8_t)) {                         \
                if (skip_size == sizeof(uint8_t)) {                    \
                    if (e_size == sizeof(uint8_t)) {                   \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint16_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint32_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
                if (skip_size == sizeof(uint16_t)) {                   \
                    if (e_size == sizeof(uint8_t)) {                   \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint16_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint32_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
            }                                                          \
            if (deg_size == sizeof(uint16_t)) {                        \
                if (skip_size == sizeof(uint16_t)) {                   \
                    if (e_size == sizeof(uint16_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint32_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
                if (skip_size == sizeof(uint32_t)) {                   \
                    if (e_size == sizeof(uint16_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint32_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
            }                                                          \
            if (deg_size == sizeof(uint32_t)) {                        \
                if (skip_size == sizeof(uint32_t)) {                   \
                    if (e_size == sizeof(uint32_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
                if (skip_size == sizeof(uint64_t)) {                   \
                    if (e_size == sizeof(uint32_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
            }                                                          \
            if (deg_size == sizeof(uint64_t)) {                        \
                if (skip_size == sizeof(uint64_t)) {                   \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
            }                                                          \
        }                                                              \
                                                                       \
        if (v_size == sizeof(uint64_t)) {                              \
            if (deg_size == sizeof(uint8_t)) {                         \
                if (skip_size == sizeof(uint8_t)) {                    \
                    if (e_size == sizeof(uint8_t)) {                   \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint16_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint32_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint8_t,                               \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
                if (skip_size == sizeof(uint16_t)) {                   \
                    if (e_size == sizeof(uint8_t)) {                   \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint8_t,                               \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint16_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint32_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint8_t,                               \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
            }                                                          \
            if (deg_size == sizeof(uint16_t)) {                        \
                if (skip_size == sizeof(uint16_t)) {                   \
                    if (e_size == sizeof(uint16_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint32_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint16_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
                if (skip_size == sizeof(uint32_t)) {                   \
                    if (e_size == sizeof(uint16_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint16_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint32_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
            }                                                          \
            if (deg_size == sizeof(uint32_t)) {                        \
                if (skip_size == sizeof(uint32_t)) {                   \
                    if (e_size == sizeof(uint32_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
                if (skip_size == sizeof(uint64_t)) {                   \
                    if (e_size == sizeof(uint32_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
            }                                                          \
            if (deg_size == sizeof(uint64_t)) {                        \
                if (skip_size == sizeof(uint64_t)) {                   \
                    if (e_size == sizeof(uint64_t)) {                  \
                        if (chunk_offset_size == sizeof(uint8_t)) {    \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint8_t>(__VA_ARGS__);                 \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint16_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint16_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint32_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint32_t>(__VA_ARGS__);                \
                        }                                              \
                        if (chunk_offset_size == sizeof(uint64_t)) {   \
                            traverse_impl<                             \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t,                              \
                                uint64_t>(__VA_ARGS__);                \
                        }                                              \
                    }                                                  \
                }                                                      \
            }                                                          \
        }                                                              \
    } while (0)
