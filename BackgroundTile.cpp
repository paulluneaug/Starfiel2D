#include "BackgroundTile.h"

#include <iostream>

#include "Hasher.h"
#include "Random.h"

BackgroundTile::BackgroundTile(const sf::Vector2i& tilePosition, float tileSize, uint32_t layerOffset, GenerationSetings& generationSettings) :
	m_tilePosition(tilePosition), m_planetShader(generationSettings.StarShader),
	m_seed(Hasher::GetSeedFromCoordinates(tilePosition.x, tilePosition.y, layerOffset))
{
	m_hasPlanet = Random::RandomBoolProb(m_seed, generationSettings.PlanetProbability);
	if (!m_hasPlanet) 
	{
		return;
	}
	
	m_center = {Random::RandomFloat01(m_seed), Random::RandomFloat01(m_seed)};

	const sf::Vector2f& sizeRange = generationSettings.PlanetsSizeRange;
	float spriteSize = MathUtils::RemapFrom01(Random::RandomFloat01(m_seed), sizeRange.x, sizeRange.y) * tileSize;
	float spriteHalfSize = spriteSize / 2.0f;

	m_spriteOffset =
	{
		tilePosition.x * tileSize + m_center.x + spriteHalfSize,
		tilePosition.y * tileSize + m_center.y + spriteHalfSize
	};

	// Texture for planet
	if (!m_texture.loadFromFile("res/planet.png"))
		std::cerr << "Failed to load planet texture" << std::endl;

	// Sprite for planet
	m_tileSprite = new sf::Sprite(m_texture);
	std::cout << spriteSize << std::endl;
	m_tileSprite->setScale({spriteSize, spriteSize});
	m_tileSprite->setOrigin(m_center);
	m_tileSprite->setColor(sf::Color(Random::RandomUInt(m_seed) | 0x000000FF));
}

void BackgroundTile::Draw(sf::RenderWindow& r_win, const sf::Vector2f& layerOrigin, const Camera& camera)
{
	if (!m_hasPlanet)
	{
		return;
	}

	m_tileSprite->setPosition(layerOrigin + m_spriteOffset);

	if (!camera.CanSee(m_tileSprite->getTextureRect())) 
	{
		return;
	}
	sf::Glsl::Vec4 noiseUV = {m_center.x, m_center.y, m_tileSprite->getScale().x/2048, m_tileSprite->getScale().y/2048};
	m_planetShader.setUniform("NoiseUV", noiseUV);
	r_win.draw(*m_tileSprite, &m_planetShader);
}
