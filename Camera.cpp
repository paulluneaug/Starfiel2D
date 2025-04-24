#include "Camera.hpp"

#include <iostream>

Camera::Camera(sf::RenderWindow& window) : m_view({0.f,0.f}, static_cast<sf::Vector2f>(window.getSize()) / 4.f)
{
}

void Camera::ChangePosition(const sf::Vector2f& playerPosition)
{
    sf::Vector2f positionDifference = playerPosition - m_view.getCenter();
    if (positionDifference.lengthSquared() < std::numeric_limits<float>::epsilon())
        m_view.setCenter(playerPosition);
    else
    {
        m_view.move(positionDifference.componentWiseMul(positionDifference).componentWiseMul(positionDifference) * CAMERA_SNAP);
    }
}

void Camera::UpdateView(sf::RenderWindow& window) const
{
    window.setView(m_view);
}

void Camera::Draw(sf::RenderWindow& window) const
{
    //window.draw(m_rectangle);
}

const sf::View& Camera::GetView() const
{
    return m_view;
}


bool Camera::CanSee(const sf::IntRect& intRect) const
{
    const sf::FloatRect& viewPort = m_view.getViewport();
    sf::FloatRect rect = sf::FloatRect(
        { static_cast<float>(intRect.position.x), static_cast<float>(intRect.position.y)},
        { static_cast<float>(intRect.size.x), static_cast<float>(intRect.position.y) });

    return viewPort.contains({ rect.position.x , rect.position.y })
        || viewPort.contains({ rect.position.x + rect.size.x, rect.position.y })
        || viewPort.contains({ rect.position.x, rect.position.y + rect.size.y })
        || viewPort.contains({ rect.position.x + rect.size.x, rect.position.y + rect.size.y });
}
