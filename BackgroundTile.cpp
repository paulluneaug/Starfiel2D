#include "BackgroundTile.h"

#include "Hasher.h"
#include "Random.h"

BackgroundTile::BackgroundTile(const sf::Vector2i& tilePosition, float tileSize, uint32_t layerOffset, const GenerationSetings& generationSettings) :
	m_tilePosition(tilePosition),
	m_seed(Hasher::GetSeedFromCoordinates(tilePosition.x, tilePosition.y, layerOffset))
{
	m_hasPlanet = Random::RandomBoolProb(m_seed, generationSettings.PlanetProbability);
	if (!m_hasPlanet) 
	{
		return;
	}

	float centerX = Random::RandomFloat01(m_seed);
	float centerY = Random::RandomFloat01(m_seed);

	const sf::Vector2f& sizeRange = generationSettings.PlanetsSizeRange;
	float spriteSize = MathUtils::RemapFrom01(Random::RandomFloat01(m_seed), sizeRange.x, sizeRange.y) * tileSize;
	float spriteHalfSize = spriteSize / 2.0f;

	m_spriteOffset =
	{
		tilePosition.x * tileSize + centerX + spriteHalfSize,
		tilePosition.y * tileSize + centerY + spriteHalfSize
	};

	m_tileSprite = new sf::CircleShape(spriteHalfSize);
	m_tileSprite->setOrigin({ 0.0f, 0.0f });
	m_tileSprite->setFillColor(sf::Color(Random::RandomUInt(m_seed)));
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

	r_win.draw(*m_tileSprite);
}
