#include "Player.hpp"

#include <iostream>

const sf::Sprite& Player::GetSprite() const
{
    return sprite;
}

Player::Player() :
    TEXTURE("res/starship.png"),
    sprite(TEXTURE),
    keyBeingPressed({
        {LEFT, false},
        {RIGHT, false},
        {UP, false},
        {DOWN, false},})
{
    sprite.setOrigin({TEXTURE.getSize().x/2.f, TEXTURE.getSize().y/2.f});
}

void Player::HandleInput(const sf::Keyboard::Scancode& scancode, bool isPressed)
{
    Direction direction = Direction(scancode);
    if (auto iterator = keyBeingPressed.find(direction); iterator != keyBeingPressed.end())
        keyBeingPressed.at(direction) = isPressed;
}

void Player::Move(float deltaTime)
{
    movementAcceleration.x += ACCELERATION * ((keyBeingPressed.at(LEFT) ? -1.f : 0.f) + (keyBeingPressed.at(RIGHT) ? 1 : 0.f));
    movementAcceleration.y += ACCELERATION * ((keyBeingPressed.at(UP) ? -1.f : 0.f) + (keyBeingPressed.at(DOWN) ? 1 : 0.f));
    ClampMovement();
        
    sprite.setPosition(sprite.getPosition() + movementAcceleration * deltaTime);
    sprite.setRotation(sf::radians(std::atan2(movementAcceleration.y, movementAcceleration.x)));
}

void Player::ClampMovement()
{
    float totalAcceleration = std::clamp(movementAcceleration.length(), 0.f, MAX_ACCELERATION);
    if (movementAcceleration != sf::Vector2f())
        movementAcceleration = movementAcceleration.normalized()*totalAcceleration;
    std::cout << totalAcceleration << std::endl;
}

void Player::Draw(sf::RenderWindow& window) const
{
    window.draw(sprite);
}

const sf::Vector2f Player::GetPosition() const
{
    return sprite.getPosition();
}
