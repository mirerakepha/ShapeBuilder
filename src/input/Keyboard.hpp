#pragma once
#include <SFML/Graphics.hpp>

class Keyboard
{
    public:
        Keyboard();

        void handleEvent(const sf::Event& event, sf::RenderWindow& window);

        void update(sf::RectangleShape& box);

    private:
        const float m_baseSpeed;
        const float m_fastSpeed;
};
