#include "ShapeManager.hpp"



void ShapeManager::spawnCircle(sf::Vector2f position, float radius)
{
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color(100, 180, 255));
    circle.setOutlineColor(sf::Color::White);
    circle.setOutlineThickness(1.f);
    circle.setOrigin(radius, radius);
    circle.setPosition(position);
    m_circles.push_back(circle);
}

void ShapeManager::undo()
{
    if (!m_circles.empty())
        m_circles.pop_back();
}

void ShapeManager::draw(sf::RenderWindow& window)
{
    for (const auto& circle : m_circles)
        window.draw(circle);
}


