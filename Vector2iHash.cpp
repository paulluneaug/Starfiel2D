#include "Vector2iHash.h"

#include "Hasher.h"

uint32_t Vector2iHash::operator()(const sf::Vector2i& vector) const
{
    return Hasher::Combine(Hasher::Hash(vector.x), Hasher::Hash(vector.y));
}
