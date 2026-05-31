#pragma once
#include <SFML/Graphics.hpp>

class Mouse 
{
    public:
        Mouse();

        void handleEvent(const sf::Event& event);
        void update(const sf::RenderWindow& window);
        void draw(sf::RenderWindow& window);

        bool isDragging() const;
        sf::Vector2f getDragStart() const;
        sf::Vector2f getPosition() const;

        sf::Vector2i getScreenPosition() const;
    private:
        sf::CircleShape m_cursor;
        sf::Vector2f m_position;
        sf::Vector2f m_dragStart;
        bool m_isDragging;
};
