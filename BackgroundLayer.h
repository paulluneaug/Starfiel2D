#pragma once
#include <queue>
#include <array>
#include <unordered_set>

#include "BackgroundTile.h"
#include "Camera.hpp"
#include "Vector2iHash.h"

class BackgroundLayer
{
private:
	static const int MAX_TILES_COUNT = 128;

	static const int TILES_COUNT_X = 10;
	static const int TILES_COUNT_Y = 10;

	std::unordered_set<sf::Vector2i, Vector2iHash> m_generatedTilesCoordinates;

	std::queue<BackgroundTile*> m_generatedTiles;

	float m_tileSize;
	uint32_t m_layerOffset;

	float m_parallaxFactor;

	const GenerationSetings& m_generationSettings;




public:
	BackgroundLayer(float tileSize, uint32_t layerOffset, float parallaxFactor, const GenerationSetings& generationSettings);
	~BackgroundLayer();

	void Draw(sf::RenderWindow& r_win, const Camera& camera);

private:

	void UpdateGeneratedTiles(const sf::View& cameraView, const sf::Vector2f& layerOrigin);
	void GenerateTile(const sf::Vector2i& tilePostion, const sf::IntRect& generatedZone);

};

