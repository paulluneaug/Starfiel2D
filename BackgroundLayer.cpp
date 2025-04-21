#include "BackgroundLayer.h"

#include <iostream>
#include "Random.h"

#include <iostream>
#include "Random.h"

BackgroundLayer::BackgroundLayer(float tileSize, uint32_t layerOffset, float parallaxFactor, GenerationSetings& generationSettings, bool isStarry) :
	m_tileSize(tileSize),
	m_layerOffset(layerOffset),
	m_parallaxFactor(parallaxFactor),
	m_generationSettings(generationSettings),
	m_isStarry(isStarry)
{

	m_generatedTilesCoordinates.reserve(MAX_TILES_COUNT);

}

BackgroundLayer::~BackgroundLayer()
{
	while (!m_generatedTiles.empty()) 
	{
		delete m_generatedTiles.front();
		m_generatedTiles.pop();
	}
}

void BackgroundLayer::UpdateGeneratedTiles(const sf::View& cameraView, const sf::Vector2f& layerOrigin)
{
	sf::Vector2f viewSize = cameraView.getSize();
	sf::Vector2f center = cameraView.getCenter() - layerOrigin;

	sf::Vector2i position
	{
		static_cast<int>((center.x - viewSize.x / 2.0f) / m_tileSize) - 1,
		static_cast<int>((center.y - viewSize.y / 2.0f) / m_tileSize) - 1
	};
	sf::Vector2i size
	{
		static_cast<int>(ceilf(viewSize.x / m_tileSize)) + 2,
		static_cast<int>(ceilf(viewSize.y / m_tileSize)) + 2
	};

	sf::IntRect generatedZone
	{
		position,
		size
	};

	for (int x = generatedZone.position.x; x <= generatedZone.position.x + generatedZone.size.x; ++x)
	{
		for (int y = generatedZone.position.y; y <= generatedZone.position.y + generatedZone.size.y; ++y)
		{
			const sf::Vector2i tile = { x, y };
			if (m_generatedTilesCoordinates.find(tile) != m_generatedTilesCoordinates.end())
			{
				continue;
			}

			GenerateTile(tile, generatedZone);
		}
	}
}

void BackgroundLayer::GenerateTile(const sf::Vector2i& tilePostion, const sf::IntRect& generatedZone)
{
	BackgroundTile* newTile = new BackgroundTile(tilePostion, m_tileSize, m_layerOffset, m_generationSettings, m_isStarry);

	if (m_generatedTiles.size() >= MAX_TILES_COUNT) 
	{
		for (int it = 0; it < MAX_TILES_COUNT; ++it) 
		{
			BackgroundTile* tile = m_generatedTiles.front();
			m_generatedTiles.pop();

			const sf::Vector2i& tileCoordinate = tile->GetCoordinates();

			if (generatedZone.contains(tileCoordinate))
			{
				m_generatedTiles.push(tile);
				continue;
			}

			m_generatedTilesCoordinates.erase(tileCoordinate);
			delete tile;
			break;
		}
	}


	m_generatedTilesCoordinates.insert(tilePostion);
	m_generatedTiles.push(newTile);
}

void BackgroundLayer::Draw(sf::RenderWindow& r_win, const Camera& camera)
{
	const sf::View& cameraView = camera.GetView();
	sf::Vector2f layerOrigin = cameraView.getCenter() * m_parallaxFactor;

	UpdateGeneratedTiles(cameraView, layerOrigin);

	for (BackgroundTile* tile : m_generatedTiles._Get_container()) 
	{
		tile->Draw(r_win, layerOrigin, camera);
	}
}
