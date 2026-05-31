#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Block.hpp"

class ShapeManager
{
    public:
        ShapeManager();

        void spawnBlock(const std::array<bool, 9>& pattern, sf::Vector2f center);
        void handleEvent(const sf::Event& event, sf::Vector2f mousePos);
        void update(sf::Vector2f mousePos, sf::Vector2u windowSize);
        void undo();
        void draw(sf::RenderWindow& window);

    private:
        std::vector<Block> m_blocks;

        int m_dragIndex;
        sf::Vector2f m_dragOffset;
        /*
        // check is a point is inside a circle
        bool hitTest(const sf::CircleShape& circle, sf::Vector2f point);

        std::vector<sf::CircleShape> m_circles;
        //w hich circle is being dragged
        int m_dragIndex;

        //offset btwn mouse and circle center
        sf::Vector2f m_dragOffset; // maintain the gap to the center while dragging

        */
};
