#pragma once
#include <queue>
#include <array>

#include "BackgroundTile.h"
#include "Camera.hpp"

class BackgroundLayer
{
private:
	static const int MAX_TILES_COUNT = 128;

	static const int TILES_COUNT_X = 10;
	static const int TILES_COUNT_Y = 10;

	//std::queue<BackgroundTile> m_tiles;
	std::array<BackgroundTile*, TILES_COUNT_X* TILES_COUNT_Y> m_tiles;

	float m_tileSize;
	uint32_t m_layerOffset;

	float m_parallaxFactor;

	GenerationSetings& m_generationSettings;




public:
	BackgroundLayer(float tileSize, uint32_t layerOffset, float parallaxFactor, GenerationSetings& generationSettings);
	~BackgroundLayer();

	void Draw(sf::RenderWindow& r_win, const Camera& camera);

private:

	void GenerateTile(const sf::Vector2i& tilePostion);

};

