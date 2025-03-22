#pragma once
#include <unordered_map>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

class Player
{
private:
    enum Direction
    {
        LEFT = sf::Keyboard::Scancode::A,
        RIGHT = sf::Keyboard::Scancode::D,
        UP = sf::Keyboard::Scancode::W,
        DOWN = sf::Keyboard::Scancode::S,
    };
    
    const float ACCELERATION = 10.f;
    const float MAX_ACCELERATION = 1.f;
    const sf::Texture TEXTURE;
    
    sf::Sprite sprite;
    std::unordered_map<Direction, bool> keyBeingPressed;
    sf::Vector2f movementAcceleration;

    
public:
    
    Player();
    void HandleInput(const sf::Keyboard::Scancode& scancode, bool isPressed);
    void Move(const float& deltaTime);
    void ClampMovement();
    const sf::Vector2f GetPosition() const;
    const sf::Sprite& GetSprite();
};
