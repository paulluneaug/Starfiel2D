#include "Background.h"

#include <iostream>
#include "Hasher.h"
#include "Lib.h"

Background::Background(GenerationSetings& generationSettings)
{
	uint32_t seed = generationSettings.Seed;
	int layerIndex = 0;
	
	//m_layers[layerIndex++] = new BackgroundLayer(100.0f, Hasher::HashRef(seed), .99f, generationSettings, true);
	m_layers[layerIndex++] = new BackgroundLayer(100.0f, Hasher::HashRef(seed), .95f, generationSettings, true);
	m_layers[layerIndex++] = new BackgroundLayer(200.0f, Hasher::HashRef(seed), .9f, generationSettings, true);
	m_layers[layerIndex++] = new BackgroundLayer(200.0f, Hasher::HashRef(seed), 0.0f, generationSettings);
	m_layers[layerIndex++] = new BackgroundLayer(150.0f, Hasher::HashRef(seed), -0.1f, generationSettings);
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
