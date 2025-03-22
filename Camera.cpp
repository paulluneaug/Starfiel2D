#include "Camera.hpp"

Camera::Camera() : m_texture("res/PSY.png"), m_rectangle({800*10,800*10}), m_view({0.f,0.f}, {400.f, 400.f})
{
    m_texture.setRepeated(true);

    m_rectangle.setPosition({0,0});
    m_rectangle.setOrigin({m_rectangle.getSize().x / 2, m_rectangle.getSize().y / 2});
    m_rectangle.setTexture(&m_texture);
    m_rectangle.setTextureRect({{0,0}, {static_cast<int>(m_texture.getSize().x*10),static_cast<int>(m_texture.getSize().y*10)}});
}

void Camera::ChangePosition(const sf::Vector2f& playerPosition)
{
    m_view.setCenter(playerPosition);
}

void Camera::UpdateView(sf::RenderWindow& window) const
{
    window.setView(m_view);
}

void Camera::Draw(sf::RenderWindow& window) const
{
    window.draw(m_rectangle);
}

const sf::View& Camera::GetView() const
{
    return m_view;
}

const sf::RectangleShape& Camera::GetRectangleShape() const
{
    return m_rectangle;
}
