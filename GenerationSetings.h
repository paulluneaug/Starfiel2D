#pragma once

#include "SFML/Graphics.hpp"

class GenerationSetings
{
public:
	sf::Vector2f PlanetsSizeRange;
	float PlanetProbability;
	sf::Texture NoiseTexure;
	sf::Shader PlanetShader;

	void Init();
};

