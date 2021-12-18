#include "CRC32Hasher.h"

#include <boost/crc.hpp> 
#include <vector>


std::vector<uint8_t> CRC32Hasher::HashBlock(std::vector<uint8_t> block)
{
    boost::crc_32_type crc32;
    crc32.process_bytes(block.data(), block.size());
    unsigned int checksum = crc32.checksum();
    auto byte_array = reinterpret_cast<uint8_t*>(&checksum);
    
    return std::vector<uint8_t>(byte_array, byte_array + sizeof(checksum));
}
