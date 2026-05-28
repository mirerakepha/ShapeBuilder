#include "ShapeManager.hpp"
#include <cmath>


ShapeManager::ShapeManager()
    : m_dragIndex(-1)   // -1 means nothing is being dragged
{}

bool ShapeManager::hitTest(const sf::CircleShape& circle, sf::Vector2f point)
{
    sf::Vector2f center = circle.getPosition();
    float radius = circle.getRadius();

    // pythagoras -> dist = sqrt((dx * dx) + (dy * dy))
    float dy = point.y - center.y;
    float dx = point.x - center.x;
    float distance = std::sqrt(dx*dx + dy*dy);

    // true if mouse is inside the radius
    return distance <= radius;
}

void ShapeManager::handleEvent(const sf::Event& event, sf::Vector2f mousePos)
{
    // left click to  pick a circle
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        // top drwan circle gets picked up first
        for (int i = static_cast<int>(m_circles.size()) -1; i >= 0; i--)
        {
            if (hitTest(m_circles[i], mousePos))
            {
                m_dragIndex = i;
                //record offset so circle doesnt snap to cursor center
                m_dragOffset = m_circles[i].getPosition() - mousePos;
                break; //only pick one circle at a time
            }
        }
        // if no circle was hit spawn a new one
        if (m_dragIndex == -1)
        {
            sf::CircleShape circle(30.f);
            circle.setFillColor(sf::Color(100, 180, 255));
            circle.setOutlineColor(sf::Color::White);
            circle.setOutlineThickness(1.f);
            circle.setOrigin(30.f, 30.f);
            circle.setPosition(mousePos);
            m_circles.push_back(circle);

        }
    }

    // drop to release
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        m_dragIndex = -1; // drop
    }
}

void ShapeManager::update(sf::Vector2f mousePos)
{
    // drag a circle
    if (m_dragIndex != -1)
    {
        m_circles[m_dragIndex].setPosition(mousePos + m_dragOffset);
    }
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


