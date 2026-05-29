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

        // return array of selected cells
        const std::array<bool, 9>& getSelectedCells() const;

    private:
        void buildGrid(); // position 9 boxes inside the Dialog
        void updateCellColors(); // change color when a cell is selected

        bool m_isOpen;
        // dark bg panel
        sf::RectangleShape m_panel;

        //boxes 3x3 ; cells
        std::array<sf::RectangleShape, 9> m_cells;

        //highlight when selected
        std::array<bool, 9> m_selected;

        //panel pos and size
        sf::Vector2f m_panelPos;
        sf::Vector2f m_panelSize;

        float m_cellSize;
        float m_padding; // space btwn pannel edge and grid
        float m_gap; // space btn individual cells
};
