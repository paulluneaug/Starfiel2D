#pragma once
#include "BackgroundLayer.h"

class Background
{
private:
	static const int LAYERS_COUNT = 2;

	std::array<BackgroundLayer*, LAYERS_COUNT> m_layers;

public:
	Background(const GenerationSetings& generationSettings);

	void Draw(sf::RenderWindow& r_win, const Camera& camera);
};

