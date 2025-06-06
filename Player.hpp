#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

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
    const float MAX_ACCELERATION = 100.f;
    const sf::Texture TEXTURE;
    
    sf::Sprite m_sprite;
    sf::Music m_reactors;
    bool m_isReactorsPlaying;
    
    std::unordered_map<Direction, bool> keyBeingPressed;
    sf::Vector2f movementAcceleration;

    
public:
    
    Player();
    void HandleInput(const sf::Keyboard::Scancode& scancode, bool isPressed);
    void Move(float deltaTime);
    void ClampMovement();

    void Draw(sf::RenderWindow& window) const;
    
    const sf::Vector2f GetPosition() const;
    const sf::Sprite& GetSprite() const;
};
