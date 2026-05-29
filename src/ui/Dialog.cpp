#include "Dialog.hpp"
#include <iostream>


Dialog::Dialog(sf::Vector2u windowSize)
    : m_isOpen(false),
      m_cellSize(60.f),
      m_padding(30.f),
      m_gap(8.f)
{
    // initialize as cells are seleceted
    m_selected.fill(false);
    //panel
    float gridWidth = 3 * m_cellSize + 2 * m_gap;
    float gridHeight = 3 * m_cellSize + 2 * m_gap;

    m_panelSize = sf::Vector2f(
            gridWidth + 2 * m_padding,
            gridHeight + 2 * m_padding + 50.f + 20.f
            );

    // center panel in the window
    m_panelPos = sf::Vector2f(
            (windowSize.x - m_panelSize.x) / 2.f,
            (windowSize.y - m_panelSize.y) / 2.f
            );

    // style
    m_panel.setSize(m_panelSize);
    m_panel.setPosition(m_panelPos);
    m_panel.setFillColor(sf::Color(45, 45, 45));
    m_panel.setOutlineColor(sf::Color(120, 120, 120));
    m_panel.setOutlineThickness(2.f);

    // build the celss
    buildGrid();
    // button
    buildButton();


}

void Dialog::buildGrid()
{
    float startX = m_panelPos.x + m_padding;
    float startY = m_panelPos.y + m_padding;

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            int index = row * 3 + col;

            float x = startX + col * (m_cellSize + m_gap);
            float y = startY + row * (m_cellSize + m_gap);

            m_cells[index].setSize(sf::Vector2f(m_cellSize, m_cellSize));
            m_cells[index].setPosition(x, y);
            m_cells[index].setFillColor(sf::Color(70, 70, 90));
            m_cells[index].setOutlineColor(sf::Color(100, 100, 120));
            m_cells[index].setOutlineThickness(1.f);
        }
    }
    updateCellColors(); //set initial colors
}

// button
void Dialog::buildButton()
{
    // fronts from system
    if (!m_font.loadFromFile("assets/font.ttf"))
    {
        std::cerr << "Could not load font\n";
    }

    float buttonWidth = m_panelSize.x - 2 * m_padding;
    float buttonHeight = 40.f;

    //button below grid with a 20ps m_gap
    float buttonX = m_panelPos.x + m_padding;
    float buttonY = m_panelPos.y + m_panelSize.y - m_padding - buttonHeight;

    m_button.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    m_button.setPosition(buttonX, buttonY);
    m_button.setFillColor(sf::Color(70, 140, 170));
    m_button.setOutlineColor(sf::Color(100, 180, 100));
    m_button.setOutlineThickness(1.f);

    //center text inside the button
    m_buttonText.setFont(m_font);
    m_buttonText.setString("Spawn");
    m_buttonText.setCharacterSize(22);
    m_buttonText.setFillColor(sf::Color::White);

    // getLocalBound() gives the actual text size
    sf::FloatRect textBounds = m_buttonText.getGlobalBounds();
    m_buttonText.setOrigin(
            textBounds.left + textBounds.width / 2.f,
            textBounds.top + textBounds.height / 2.f
            );
    m_buttonText.setPosition(
            buttonX + buttonWidth / 2.f,
            buttonY + buttonHeight / 2.f
            );
}

void Dialog::updateCellColors()
{
    for (int i = 0; i < 9; i++)
    {
        if (m_selected[i])
            m_cells[i].setFillColor(sf::Color(100, 200, 255)); //selected
        else
            m_cells[i].setFillColor(sf::Color(70, 70, 90)); // unselected
                
    }
}

void Dialog::toggle()
{
    m_isOpen = !m_isOpen;
}

bool Dialog::isOpen() const
{
    return m_isOpen;
}

bool Dialog::wasConfirmed()
{
    if (m_confirmed)
    {
        m_confirmed = false; // reset so it firs only once
        return true;
    }
    return false;
}


const std::array<bool, 9>& Dialog::getSelectedCells() const
{
    return m_selected;
}

void Dialog::handleEvent(const sf::Event& event)
{
    if (!m_isOpen) return; // ignore events when closed

    // close on Escape
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            m_isOpen = false;
        }
    }

    // click cell
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f clickPos(
                static_cast<float>(event.mouseButton.x),
                static_cast<float>(event.mouseButton.y)
                );

        for (int i = 0; i < 9; i++)
        {
            if (m_cells[i].getGlobalBounds().contains(clickPos))
            {
                m_selected[i] = !m_selected[i]; // toggle on/off
                updateCellColors();
                break; // one cell per click
            }
        }
        // check button -> send to main.cpp and close dalog
        if (m_button.getGlobalBounds().contains(clickPos))
        {
            m_confirmed = true;
            m_isOpen = false;
        }
    }
}


void Dialog::draw(sf::RenderWindow& window)
{
    if (!m_isOpen) return; // nothing bcs its closed

    window.draw(m_panel);

    for(const auto& cell : m_cells)
        window.draw(cell);

    window.draw(m_button);
    window.draw(m_buttonText);
}













