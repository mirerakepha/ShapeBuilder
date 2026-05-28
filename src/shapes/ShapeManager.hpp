#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class ShapeManager
{
    public:
        void spawnCircle(sf::Vector2f position, float radius = 20.f);
        void undo();
        void draw(sf::RenderWindow& window);

    private:
        std::vector<sf::CircleShape> m_circles;
};
