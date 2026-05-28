#include "Keyboard.hpp"
#include <iostream>

Keyboard::Keyboard()
    : m_baseSpeed(4.f), m_fastSpeed(10.f)
{}

void Keyboard::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
            window.close();
        if (event.key.code == sf::Keyboard::R){
            std::cout << "Reset\n";
        }
    }
}


void Keyboard::update(sf::RectangleShape& box)
{
    bool shiftHeld = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);

    float speed = shiftHeld ? m_fastSpeed : m_baseSpeed;

    sf::Vector2f pos = box.getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) pos.y -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) pos.x -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) pos.y += speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) pos.x += speed;

    pos.x = std::max(20.f, std::min(pos.x, 980.f));
    pos.y = std::max(20.f, std::min(pos.y, 780.f));

    box.setPosition(pos);
}


