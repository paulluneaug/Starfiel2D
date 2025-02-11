#include "EntryPoint.h"
#include <SFML/Graphics.hpp>

#include <iostream>


int main()
{
	sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");
	std::cout << "Hello World" << std::endl;

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }
    }

	return 0;
}
