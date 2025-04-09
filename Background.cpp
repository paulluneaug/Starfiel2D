#include "Background.h"
#include "Random.h"

Background::Background(const GenerationSetings& generationSettings)
{
	uint32_t seed = generationSettings.Seed;


	for (int iLayer = 0; iLayer < LAYERS_COUNT; ++iLayer) 
	{
		m_layers[LAYERS_COUNT - iLayer - 1] = new BackgroundLayer(300.0f / iLayer, Random::RandomUInt(seed), 0.9f / iLayer, generationSettings);
	}
}

Background::~Background()
{
	for (BackgroundLayer* layer : m_layers) {
		delete layer;
	}
}

void Background::Draw(sf::RenderWindow& r_win, const Camera& camera)
{
	for (BackgroundLayer* layer : m_layers) 
	{
		layer->Draw(r_win, camera);
	}
}
