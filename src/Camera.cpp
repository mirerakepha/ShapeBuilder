#include "Camera.hpp"

Camera::Camera(sf::Vector2u windowSize)
    : m_offset(0.f, 0.f),
    m_panSpeed(6.f)
{
    // world view starts centerd on the window
    m_worldView.setSize(
            static_cast<float>(windowSize.x),
            static_cast<float>(windowSize.y)
            );
    m_worldView.setCenter(
            windowSize.x / 2.f,
            windowSize.y / 2.f
            );

    // ui view matches the window;; never moves
    m_uiView.setSize(
            static_cast<float>(windowSize.x),
            static_cast<float>(windowSize.y)
            );
    m_uiView.setCenter(
            windowSize.x / 2.f,
            windowSize.y / 2.f
            );
}

void Camera::handleEvent(const sf::Event& event)
{
    // pan vertically on scroll
    if (event.type == sf::Event::MouseWheelScrolled)
    {
        float delta = event.mouseWheelScroll.delta * 30.f;
        m_worldView.move(0.f, delta);
        m_offset.y -= delta;
    }
}

void Camera::update()
{
    // arrow key panning
    sf::Vector2f move(0.f, 0.f);

    // arrow keys navigate the world
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) move.x -= m_panSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) move.x += m_panSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) move.y -= m_panSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) move.y += m_panSpeed;

    m_worldView.move(move);
    m_offset += move;
}


void Camera::applyWorldView(sf::RenderWindow& window)
{
    window.setView(m_worldView);
}

void Camera::applyUIView(sf::RenderWindow& window)
{
    window.setView(m_uiView);
}

sf::Vector2f Camera::screenToWorld(
        sf::RenderWindow& window,
        sf::Vector2i screenPos
        ) const
{
    // convert screen pixels to world coordinates
    return window.mapPixelToCoords(screenPos, m_worldView);
}

sf::Vector2f Camera::getOffset() const
{
    return m_offset;
}












