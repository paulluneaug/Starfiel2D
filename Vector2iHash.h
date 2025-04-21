#pragma once

#include "SFML/Graphics.hpp"

struct Vector2iHash
{
	uint32_t operator()(const sf::Vector2i& vector) const;
};

