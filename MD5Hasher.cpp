#include "MD5Hasher.h"
#include <boost/uuid/detail/md5.hpp>


std::vector<uint8_t> MD5Hasher::HashBlock(std::vector<uint8_t> block)
{
    boost::uuids::detail::md5 hash;
    boost::uuids::detail::md5::digest_type digest;
    hash.process_bytes(block.data(), block.size());
    hash.get_digest(digest);
    auto byte_array = reinterpret_cast<uint8_t*>(digest);
    
    return std::vector<uint8_t>(byte_array, byte_array + sizeof(digest));
}
