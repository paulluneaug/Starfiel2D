#pragma once
#include <cstdint>
class Hasher
{
public:
    
	static uint32_t Hash(uint32_t s);
	static uint32_t HashRef(uint32_t& s);
	static uint32_t GetSeedFromCoordinates(int x, int y, uint32_t offset);

	static uint32_t Combine(uint32_t a, uint32_t b);

};

