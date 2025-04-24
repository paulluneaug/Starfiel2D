#pragma once
#include <SFML/Graphics.hpp>

class Camera
{
private:
    const float CAMERA_SNAP = 0.000001f;
    
    sf::View m_view;


public:
    Camera(sf::RenderWindow& window);
    void ChangePosition(const sf::Vector2f& playerPosition);

    void UpdateView(sf::RenderWindow& window) const;
    void Draw(sf::RenderWindow& window) const;
    
    const sf::View& GetView() const;

    bool CanSee(const sf::IntRect& rect) const;
};
