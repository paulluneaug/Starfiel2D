#pragma once
#include "BackgroundLayer.h"

class Background
{
private:
	static const int LAYERS_COUNT = 4;

	std::array<BackgroundLayer*, LAYERS_COUNT> m_layers;

public:
	Background(GenerationSetings& generationSettings);
	~Background();

	void Draw(sf::RenderWindow& r_win, const Camera& camera);
};

