#include "Ball.hpp"

Ball::Ball()
    :m_active(false)
{
    m_shape.setRadius(RADIUS);
    m_shape.setOrigin(RADIUS, RADIUS);
    m_shape.setFillColor(sf::Color(240, 220, 80));
    m_shape.setOutlineColor(sf::Color(200, 180, 40));
    m_shape.setOutlineThickness(2.f);

    reset();

}

void Ball::reset()
{
    m_active = false;
    m_velocity = sf::Vector2f(0.f, 0.f);
    m_shape.setPosition(SPAWN_X, SPAWN_Y);
}

void Ball::setActive(bool active)
{
    m_active = active;

    if (active)
        m_velocity = sf::Vector2f(120.f, 0.f); // pixels per sec
}

bool Ball::isActive() const 
{
    return m_active;
}

sf::Vector2f Ball::getPosition() const
{
    return m_shape.getPosition();
}

float Ball::getRadius() const
{
    return RADIUS;
}

void Ball::update(float dt)
{
    if (!m_active) return;

    //gravity
    const float GRAVITY = 500.f;
    m_velocity.y += GRAVITY * dt; //delta time
    m_shape.move(m_velocity * dt);
}

void Ball::draw(sf::RenderWindow& window)
{
    window.draw(m_shape);
}
