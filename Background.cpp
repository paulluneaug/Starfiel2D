#include "Background.h"

#include <iostream>

Background::Background(GenerationSetings& generationSettings)
{
	m_layers[0] = new BackgroundLayer(100.0f, 2000000u, .9f, generationSettings, true);
	m_layers[1] = new BackgroundLayer(200.0f, 0u, 0.0f, generationSettings);
	m_layers[2] = new BackgroundLayer(150.0f, 1321354u, -0.1f, generationSettings);
}

Background::~Background()
{
	for (BackgroundLayer* layer : m_layers) {
		delete layer;
	}
}

void Background::Draw(sf::RenderWindow& r_win, const Camera& camera)
{
	for (BackgroundLayer* layer : m_layers) {
		layer->Draw(r_win, camera);
	}
}
