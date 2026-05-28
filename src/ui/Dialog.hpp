#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class Dialog
{
    public:
        Dialog(sf::Vector2u windowSize);

        void toggle();
        bool isOpen() const;

        void handleEvent(const sf::Event& event);
        void draw(sf::RenderWindow& window);

    private:
        void buildGrid(); // position 9 boxes inside the Dialog

        bool m_isOpen;
        // dark bg panel
        sf::RectangleShape m_panel;

        //boxes 3x3
        std::array<sf::RectangleShape, 9> m_cells;

        //panel pos and size
        sf::Vector2f m_panelPos;
        sf::Vector2f m_panelSize;

        float m_cellSize;
        float m_padding; // space btwn pannel edge and grid
        float m_gap; // space btn individual cells
};
