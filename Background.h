#pragma once
#include "BackgroundLayer.h"

class Background
{
private:
	static const int LAYERS_COUNT = 5;

	std::array<BackgroundLayer*, LAYERS_COUNT> m_layers;

public:
	Background(const GenerationSetings& generationSettings);
	~Background();

	void Draw(sf::RenderWindow& r_win, const Camera& camera);
};

