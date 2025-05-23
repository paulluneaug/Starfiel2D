#pragma once

#include "SFML/Graphics.hpp"

class GenerationSetings
{
public:
	sf::Vector2f PlanetsSizeRange;
	float PlanetProbability;

	uint32_t Seed;
	sf::Texture NoiseTexure;
	sf::Shader PlanetShader, StarShader;

	void Init();
};

