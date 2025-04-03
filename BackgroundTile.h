#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "Camera.hpp"
#include "GenerationSetings.h"

class BackgroundTile
{
private:
	sf::Vector2i m_tilePosition;

	/// <summary>
	/// Sprite position in the tile layer's repère
	/// </summary>
	sf::Vector2f m_spriteOffset;
	sf::FloatRect m_spriteRect;

	uint32_t m_seed;

	sf::Shape* m_tileSprite;

	bool m_hasPlanet;

public:
	BackgroundTile(const sf::Vector2i& tilePosition, float tileSize, uint32_t layerOffset, const GenerationSetings& generationSettings);
	void Draw(sf::RenderWindow& r_win, const sf::Vector2f& layerOrigin, const Camera& camera);

private:
	//sf::Vector2f GetSpritePosition();


};

