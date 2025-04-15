#pragma once
#include <SFML/Graphics.hpp>

class Camera
{
private:
    const float CAMERA_SNAP = 0.000001f;
    
    sf::Texture m_texture;
    sf::RectangleShape m_rectangle;
    sf::View m_view;


public:
    Camera();
    void ChangePosition(const sf::Vector2f& playerPosition);

    void UpdateView(sf::RenderWindow& window) const;
    void Draw(sf::RenderWindow& window) const;
    
    const sf::View& GetView() const;
    const sf::RectangleShape& GetRectangleShape() const;
};
