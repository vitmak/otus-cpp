#pragma once

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>


class Hasher
{
public:
    virtual std::vector<uint8_t> HashBlock(std::vector<uint8_t> block) = 0;  
};