#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class ShapeManager
{
    public:
        ShapeManager();

        void handleEvent(const sf::Event& event, sf::Vector2f mousePos);
        void update(sf::Vector2f mousePos);
        void undo();
        void draw(sf::RenderWindow& window);

    private:
        // check is a point is inside a circle
        bool hitTest(const sf::CircleShape& circle, sf::Vector2f point);

        std::vector<sf::CircleShape> m_circles;
        //w hich circle is being dragged
        int m_dragIndex;

        //offset btwn mouse and circle center
        sf::Vector2f m_dragOffset; // maintain the gap to the center while dragging

};
