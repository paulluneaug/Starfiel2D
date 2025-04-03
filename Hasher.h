#pragma once
#include <cstdint>
class Hasher
{
public:
	static uint32_t GetSeedFromCoordinates(int x, int y, uint32_t offset);

};

