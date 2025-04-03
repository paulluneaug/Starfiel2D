#include "Hasher.h"

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
