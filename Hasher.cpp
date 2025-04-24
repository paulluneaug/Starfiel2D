#include "Hasher.h"

uint32_t Hasher::Hash(uint32_t s)
{
    s ^= 2747636419u;
    s *= 2654435769u;
    s ^= s >> 16;
    s *= 2654435769u;
    s ^= s >> 16;
    s *= 2654435769u;
    return s;
}

uint32_t Hasher::HashRef(uint32_t& s)
{
    s = Hasher::Hash(s);
    return s;
}

uint32_t Hasher::GetSeedFromCoordinates(int x, int y, uint32_t offset)
{
    uint32_t w = 8 * 4;
    uint32_t s = w / 2;
    uint32_t a = x, b = y;
    a *= 3284157443;
    b ^= a << s | a >> w - s;
    b += offset;
    b *= 1911520717;
    a ^= b << s | b >> w - s;
    a *= 2048419325;
    return a;
}

uint32_t Hasher::Combine(uint32_t a, uint32_t b)
{
    return a ^ (Hash(b) + 0x9e3779b9 + (a << 6) + (a >> 2));
}
