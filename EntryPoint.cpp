#include "EntryPoint.h"
#include <SFML/Graphics.hpp>

#include <iostream>

#include "Player.hpp"


int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "StarField2D", sf::Style::Close, sf::State::Windowed);
	std::cout << "Hello World" << std::endl;

    Player player;

    while (window.isOpen())
    {
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
        player.Move();

        window.clear();
        window.draw(player.GetSprite());
        window.display();
    }

	return 0;
}
