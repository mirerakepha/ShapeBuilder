#include "Mouse.hpp"
#include <iostream>

Mouse::Mouse()
    : m_isDragging(false)
{
    m_cursor.setRadius(5.f);
    m_cursor.setOrigin(5.f, 5.f);
    m_cursor.setFillColor(sf::Color(255, 100, 100));
}
void Mouse::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        m_isDragging = true;
        m_dragStart = sf::Vector2f(
                static_cast<float>(event.mouseButton.x),
                static_cast<float>(event.mouseButton.y)
                );
        // std::cout << "Drag started: ";
            //<< m_dragStart.x ", " << m_dragStart.y "\n";
    }
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left){
        m_isDragging = false;
    }
    if (event.type == sf::Event::MouseWheelScrolled){
        if (event.mouseWheelScroll.delta > 0)
            std::cout << "Scrolled up\n";
        else
            std::cout << "Scrolled down\n";
    }
}
void Mouse::update(const sf::RenderWindow& window){
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    m_position = sf::Vector2f(
            static_cast<float>(mousePos.x),
            static_cast<float>(mousePos.y)
            );
    m_cursor.setPosition(m_position);
    m_cursor.setFillColor(
            m_isDragging
                ? sf::Color(100, 255, 100)
                : sf::Color(255, 100, 100)
            );
}
  
void Mouse::draw(sf::RenderWindow& window)
{
    window.draw(m_cursor);
}

bool Mouse::isDragging() const 
{
    return m_isDragging;
}
sf::Vector2f Mouse::getDragStart() const
{
    return m_dragStart;
}
sf::Vector2f Mouse::getPosition() const
{
    return m_position;
}

sf::Vector2i Mouse::getScreenPosition() const
{
    return sf::Vector2i(
            static_cast<int>(m_position.x),
            static_cast<int>(m_position.y)
            );
}
