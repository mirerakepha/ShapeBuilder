#pragma once
#include <SFML/Graphics.hpp>
#include <array>
 

struct MaterialEntry
{
    std::string name;
    sf::Color color; // placeholder before loading texture
    int count; // no of times clickes -> spawn those many times
    sf::RectangleShape box; 
    sf::Text nameText;
    sf::Text countText;
};


class Dialog
{
    public:
        Dialog(sf::Vector2u windowSize);

        void toggle();
        bool isOpen() const;
        bool wasConfirmed(); // true when confir button is clicked and reset Dialog
        int getConfirmedTab() const; // the tab active when spawn is clicked
                                     //
        void handleEvent(const sf::Event& event);
        void draw(sf::RenderWindow& window);

        // tab1
        // return array of selected cells
        const std::array<bool, 9>& getSelectedCells() const;

        //tab2
        const std::vector<MaterialEntry>& getMaterials() const;
        void resetMaterialsCount();

    private:
        void buildTabs();
        void buildMaterials();
        void updateTabAppearance();
        void buildGrid(); // position 9 boxes inside the Dialog
        void buildButton(); // button position and style
        void updateCellColors(); // change color when a cell is selected

        void centerTextIn(sf::Text& text, const sf::FloatRect& rect); // center text inside a rectangle
        
        bool m_isOpen;
        bool m_confirmed;
        int m_activeTab;
        int m_confirmedTab;

        sf::Font m_font;
        // dark bg panel
        sf::RectangleShape m_panel;

        //tab buttons
        std::array<sf::RectangleShape, 2> m_tabButtons;
        std::array<sf::Text, 2> m_tabLabels;

        // == tab1
        //boxes 3x3 ; cells
        std::array<sf::RectangleShape, 9> m_cells;
        //highlight cell when selected
        std::array<bool, 9> m_selected;

        //== tab2
        std::vector<MaterialEntry> m_materials;

        //button
        sf::RectangleShape m_button;
        sf::Text m_buttonText;

        //panel pos and size
        sf::Vector2f m_panelPos;
        sf::Vector2f m_panelSize;

        float m_cellSize;
        float m_padding; // space btwn pannel edge and grid
        float m_gap; // space btn individual cells
        float m_tabBarHeight;
        float m_contentStartY; // where content begins,,,below the tab


};
