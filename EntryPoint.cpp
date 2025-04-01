#include "EntryPoint.h"
#include <SFML/Graphics.hpp>

#include <iostream>

#include "Camera.hpp"
#include "Player.hpp"
#include "Lib.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "StarField2D", sf::Style::Close, sf::State::Windowed);
    std::cout << "Hello World" << std::endl;

    // Background
    
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
        
        camera.Draw(window);
        player.Draw(window);
        
        window.display();

        frameEnd = Lib::GetTimeStamp();
    }

	return 0;
}