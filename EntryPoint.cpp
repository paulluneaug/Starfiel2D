#include "EntryPoint.h"
#include <SFML/Graphics.hpp>

#include <iostream>

#include "Background.h"
#include "Camera.hpp"
#include "Lib.h"
#include "Player.hpp"


int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "StarField2D", sf::Style::Close, sf::State::Windowed);
	std::cout << "Hello World" << std::endl;

	// Background

	GenerationSetings generationSettings;
	generationSettings.PlanetsSizeRange = { 0.01f, 0.05f };
	generationSettings.PlanetProbability = 0.8f;
	if (!generationSettings.NoiseTexure.loadFromFile("res/noiseTexture.png"))
		std::cerr << "Failed to load noise texture" << std::endl;
	if (!generationSettings.PlanetShader.loadFromFile("Shaders/planet_shader.vert", "Shaders/planet_shader.frag"))
		std::cerr << "Shader didnt load well" << std::endl;
	if (!generationSettings.StarShader.loadFromFile("Shaders/star.vert", "Shaders/star.frag"))
		std::cerr << "Shader didnt load well" << std::endl;
	generationSettings.Init();

	Background background{ generationSettings };

	Player player;
	Camera camera;


	double frameStart = 0.0;
	double frameEnd = 0.0;

	while (window.isOpen())
	{
		float deltaTime = static_cast<float>(frameEnd - frameStart);
		frameStart = Lib::GetTimeStamp();

		// check all the window's events that were triggered since the last iteration of the loop
		while (const std::optional event = window.pollEvent())
		{
			// "close requested" event: we close the window
			if (event->is<sf::Event::Closed>())
				window.close();

			if (const sf::Event::KeyPressed* keyPressed = event->getIf<sf::Event::KeyPressed>())
				player.HandleInput(keyPressed->scancode, true);
			if (const sf::Event::KeyReleased* keyReleased = event->getIf<sf::Event::KeyReleased>())
				player.HandleInput(keyReleased->scancode, false);
		}
		player.Move(deltaTime);

		// Camera work
		camera.ChangePosition(player.GetPosition());
		camera.UpdateView(window);

		window.clear();

		background.Draw(window, camera);
		camera.Draw(window);
		player.Draw(window);

		window.display();

		frameEnd = Lib::GetTimeStamp();
	}

	return 0;
}