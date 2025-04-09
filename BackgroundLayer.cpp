#include "BackgroundLayer.h"

BackgroundLayer::BackgroundLayer(float tileSize, uint32_t layerOffset, float parallaxFactor, GenerationSetings& generationSettings) :
	m_tileSize(tileSize),
	m_layerOffset(layerOffset),
	m_parallaxFactor(parallaxFactor),
	m_generationSettings(generationSettings)
{
	for (int ix = 0; ix < TILES_COUNT_X; ++ix) 
	{
		for (int iy = 0; iy < TILES_COUNT_Y; ++iy)
		{
			GenerateTile({ ix, iy });
		}
	}
}

BackgroundLayer::~BackgroundLayer()
{
	for (BackgroundTile* tile : m_tiles)
	{
		delete tile;
	}
}

void BackgroundLayer::GenerateTile(const sf::Vector2i& tilePostion)
{
	m_tiles[tilePostion.x + tilePostion.y * TILES_COUNT_X] = new BackgroundTile(tilePostion, m_tileSize, m_layerOffset, m_generationSettings);
}

void BackgroundLayer::Draw(sf::RenderWindow& r_win, const Camera& camera)
{
	sf::Vector2f layerPosition = camera.GetView().getCenter() * m_parallaxFactor;


	for (BackgroundTile* tile : m_tiles) 
	{
		tile->Draw(r_win, layerPosition, camera);
	}
}
