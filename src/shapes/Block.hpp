#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>

//one square inside a block
struct Cell 
{
    sf::RectangleShape shape;
    sf::Vector2f localOffset;
};

class Block 
{
    public:
        // pattern -> 9 bools from dialog
        Block(const std::array<bool, 9>& pattern, sf::Vector2f anchor);

        void setPosition(sf::Vector2f pos);
        sf::Vector2f getPosition() const;
        //true if point is inside the square of the block
        bool contains(sf::Vector2f point) const;
        void draw(sf::RenderWindow& window);
    private:
        std::vector<Cell> m_cells; // only the selected squares
        sf::Vector2f m_anchor; // current world posiition
        float m_cellSize; // size of each square
};
