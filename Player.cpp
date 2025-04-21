#include "Player.hpp"

#include <iostream>

const sf::Sprite& Player::GetSprite() const
{
    return m_sprite;
}

Player::Player() :
    TEXTURE("res/starship.png"),
    m_sprite(TEXTURE),
    keyBeingPressed({
        {LEFT, false},
        {RIGHT, false},
        {UP, false},
        {DOWN, false},}),
    m_reactors("res/reactors.wav")
{
    m_sprite.setOrigin({TEXTURE.getSize().x/2.f, TEXTURE.getSize().y/2.f});
    m_reactors.setLoopPoints({sf::milliseconds(500),m_reactors.getDuration()-sf::milliseconds(2000)});
    m_reactors.setLooping(true);
}

void Player::HandleInput(const sf::Keyboard::Scancode& scancode, bool isPressed)
{
    Direction direction = Direction(scancode);
    if (auto iterator = keyBeingPressed.find(direction); iterator != keyBeingPressed.end())
        keyBeingPressed.at(direction) = isPressed;
}

void Player::Move(float deltaTime)
{
    int xAcceleration = (keyBeingPressed.at(LEFT) ? -1 : 0) + (keyBeingPressed.at(RIGHT) ? 1 : 0);
    int yAcceleration = (keyBeingPressed.at(UP) ? -1 : 0) + (keyBeingPressed.at(DOWN) ? 1 : 0);
    movementAcceleration.x += ACCELERATION * static_cast<float>(xAcceleration);
    movementAcceleration.y += ACCELERATION * static_cast<float>(yAcceleration);

    if (xAcceleration != 0 || yAcceleration != 0)
    {
        if (!m_isReactorsPlaying)
        {
            m_reactors.play();
            m_isReactorsPlaying = true;
        }
    }
    else if (m_isReactorsPlaying)
    {
        m_reactors.stop();
        m_isReactorsPlaying = false;
    }
    
    ClampMovement();
        
    m_sprite.setPosition(m_sprite.getPosition() + movementAcceleration * deltaTime);
    m_sprite.setRotation(sf::radians(std::atan2(movementAcceleration.y, movementAcceleration.x)));

    //std::cout << 1.0f / deltaTime << std::endl;
}

void Player::ClampMovement()
{
    float totalAcceleration = std::clamp(movementAcceleration.length(), 0.f, MAX_ACCELERATION);
    if (movementAcceleration != sf::Vector2f())
        movementAcceleration = movementAcceleration.normalized()*totalAcceleration;
    //std::cout << totalAcceleration << std::endl;
}

void Player::Draw(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
}

const sf::Vector2f Player::GetPosition() const
{
    return m_sprite.getPosition();
}
