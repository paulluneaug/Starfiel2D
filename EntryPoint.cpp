#include "EntryPoint.h"
#include <SFML/Graphics.hpp>

#include <iostream>

#include "Player.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "StarField2D", sf::Style::Close, sf::State::Windowed);
    std::cout << "Hello World" << std::endl;

    // Background
    sf::Texture windowTexture("res/PSY.png");
    windowTexture.setRepeated(true);
    sf::RectangleShape rectangleWindow({800*10,800*10});
    rectangleWindow.setPosition({0,0});
    rectangleWindow.setOrigin({rectangleWindow.getSize().x / 2, rectangleWindow.getSize().y / 2});
    rectangleWindow.setTexture(&windowTexture);
    rectangleWindow.setTextureRect({{0,0}, {static_cast<int>(windowTexture.getSize().x*10),static_cast<int>(windowTexture.getSize().y*10)}});
    
    Player player;
    sf::View cameraView({0.f,0.f}, {400.f, 400.f});
    sf::Clock deltaTime; deltaTime.start();

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
        player.Move(deltaTime.getElapsedTime().asSeconds());

        cameraView.setCenter(player.GetPosition());
        window.setView(cameraView);

        window.clear();
        window.draw(rectangleWindow);
        window.draw(player.GetSprite());
        window.display();
        deltaTime.restart();
    }

	return 0;
}
