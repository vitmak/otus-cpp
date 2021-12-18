#pragma once

#include "Hasher.h"


class MD5Hasher : public Hasher
{
public:
    std::vector<uint8_t> HashBlock(std::vector<uint8_t> block) override;
};
