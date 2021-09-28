#include <openssl/sha.h>
#include <cstdint>
#include <iomanip>
#include <limits>
#include <sstream>
#include <string>

uint8_t get_unsigned_type_size(uint64_t val) {
    if (val > std::numeric_limits<uint32_t>::max()) {
        return sizeof(uint64_t);
    } else if (val > std::numeric_limits<uint16_t>::max()) {
        return sizeof(uint32_t);
    } else if (val > std::numeric_limits<uint8_t>::max()) {
        return sizeof(uint16_t);
    } else {
        return sizeof(uint8_t);
    }
}

std::string GetHexRepresentation(const unsigned char* Bytes, size_t Length) {
    std::ostringstream os;
    os.fill('0');
    os << std::hex;
    for (const unsigned char* ptr = Bytes; ptr < Bytes + Length; ptr++)
        os << std::setw(2) << (unsigned int)*ptr;
    return os.str();
}

std::string get_sha_sum(void* data, size_t size) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1((const unsigned char*)data, size, hash);
    return GetHexRepresentation(hash, SHA_DIGEST_LENGTH);
}
