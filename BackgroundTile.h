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
	sf::Vector2f m_center;

	/// <summary>
	/// Sprite position in the tile layer's rep�re
	/// </summary>
	sf::Vector2f m_spriteOffset;
	sf::FloatRect m_spriteRect;

	uint32_t m_seed;

	sf::Texture m_texture;
	sf::Sprite* m_tileSprite;
	sf::Shader& m_planetShader;
	sf::Shader& m_starShader;

	bool m_hasPlanet;
	bool m_isStar;

public:
	BackgroundTile(const sf::Vector2i& tilePosition, float tileSize, uint32_t layerOffset, GenerationSetings& generationSettings, bool isStar);
	~BackgroundTile();

	void Draw(sf::RenderWindow& r_win, const sf::Vector2f& layerOrigin, const Camera& camera);

	const sf::Vector2i& GetCoordinates();

private:
	//sf::Vector2f GetSpritePosition();


};

