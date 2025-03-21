#include "Player.hpp"

const sf::Sprite& Player::GetSprite()
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
{}

void Player::HandleInput(sf::Keyboard::Scancode scancode, bool isPressed)
{
    Direction direction = Direction(scancode);
    if (auto iterator = keyBeingPressed.find(direction); iterator != keyBeingPressed.end())
        keyBeingPressed.at(direction) = isPressed;
}

void Player::Move()
{
    movementAcceleration.x += ACCELERATION * ((keyBeingPressed.at(LEFT) ? -1.f : 0.f) + (keyBeingPressed.at(RIGHT) ? 1 : 0.f));
    movementAcceleration.y += ACCELERATION * ((keyBeingPressed.at(UP) ? -1.f : 0.f) + (keyBeingPressed.at(DOWN) ? 1 : 0.f));
    sprite.setPosition(sprite.getPosition() + movementAcceleration);

    sprite.setRotation(sf::radians(std::atan2(movementAcceleration.y, movementAcceleration.x)));
}
