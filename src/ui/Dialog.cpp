#include "Dialog.hpp"
#include <iostream>

static sf::Text makeText(const sf::Font& font, const std::string& str, unsigned int size,sf::Color color)
{
    sf::Text t;
    t.setFont(font);
    t.setString(str);
    t.setCharacterSize(size);
    return t;
}

Dialog::Dialog(sf::Vector2u windowSize)
    : m_isOpen(false),
      m_confirmed(false),
      m_activeTab(0), // the selct blocks tab's the one on by default on opening te Dialog
      m_confirmedTab(0),
      m_cellSize(60.f),
      m_padding(30.f),
      m_gap(8.f),
      m_tabBarHeight(35.f)
{
    // initialize as cells are seleceted
    m_selected.fill(false);
    //panel
    float gridWidth = 3 * m_cellSize + 2 * m_gap;
    float contentHeight = 5 * 44.f; // 5 materials at 44 px
    float buttonHeight = 40.f;

    m_panelSize = sf::Vector2f(
            gridWidth + 2 * m_padding,
            m_padding + m_tabBarHeight + 10.f/*btn tab & content*/ + contentHeight + 15.f/*btn content & btn*/ + buttonHeight + m_padding
            );

    // center panel in the window
    m_panelPos = sf::Vector2f(
            (windowSize.x - m_panelSize.x) / 2.f,
            (windowSize.y - m_panelSize.y) / 2.f
            );
    // content starts
    m_contentStartY = m_panelPos.y + m_padding + m_tabBarHeight + 10.f;

    // style
    m_panel.setSize(m_panelSize);
    m_panel.setPosition(m_panelPos);
    m_panel.setFillColor(sf::Color(45, 45, 45));
    m_panel.setOutlineColor(sf::Color(120, 120, 120));
    m_panel.setOutlineThickness(2.f);

    buildTabs();
    buildGrid();
    buildMaterials();
    buildButton();


}

void Dialog::centerTextIn(sf::Text& text, const sf::FloatRect& rect)
{
    sf::FloatRect tb = text.getLocalBounds(); // text actual rendersize
    
    // origin to center of the text
    text.setOrigin(
            tb.left + tb.width / 2.f,
            tb.top + tb.height / 2.f
            );
    // etxt at rect center
    text.setPosition(
            rect.left + rect.width / 2.f,
            rect.top + rect.height / 2.f
            );

}

void Dialog::buildTabs()
{
    // two tabs share the full width - padding with a 4 px gap btwn
    float totalW = m_panelSize.x - 2 * m_padding;
    float tabW = (totalW - 4.f) / 2.f;
    float tabH = m_tabBarHeight;
    float startX = m_panelPos.x + m_padding;
    float startY = m_panelPos.y + m_padding;

    const char* labels[] = {"Blocks", "Material"};

    for (int i = 0; i < 2; i++)
    {
        float x = startX + i * (tabW + 4.f);
        m_tabButtons[i].setSize(sf::Vector2f(tabW, tabH));
        m_tabButtons[i].setPosition(x, startY);
        m_tabButtons[i].setOutlineThickness(1.f);
        m_tabButtons[i].setOutlineColor(sf::Color(120, 120, 140));

        m_tabLabels[i] = makeText(m_font, labels[i], 18, sf::Color::White);

        //center the label inside the tab box
        centerTextIn(m_tabLabels[i], sf::FloatRect(x, startY, tabW, tabH));
    }
    updateTabAppearance();

}


void Dialog::buildGrid()
{
    float startX = m_panelPos.x + m_padding;
    float startY = m_contentStartY;

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

void Dialog::buildMaterials()
{
    struct MaterialDef {
        std::string name;
        sf::Color color;
    };
    std::vector<MaterialDef> defs = {
        {"Wood", sf::Color(139, 90, 43)},
        {"Steel", sf::Color(150, 160, 170)},
        {"Iron", sf::Color(80, 80, 90)},
        {"Plastic", sf::Color(220, 200, 60)},
        {"Glass", sf::Color(180, 220, 255)},
    };

    float rowHeight = 44.f;
    float boxSize = 32.f;
    float startX = m_panelPos.x + m_padding;
    float rightEdge = m_panelPos.x + m_panelSize.x - m_padding;

    for (int i = 0; i < (int)defs.size(); i++)
    {
        MaterialEntry entry;
        entry.name = defs[i].name;
        entry.color = defs[i].color;
        entry.count = 0;

        float rowY = m_contentStartY + i * rowHeight;

        // colored square --> what you click
        entry.box.setSize(sf::Vector2f(boxSize, boxSize));
        entry.box.setPosition(startX, rowY + (rowHeight - boxSize) / 2.f);
        entry.box.setFillColor(defs[i].color);
        entry.box.setOutlineColor(sf::Color(200, 200, 200));
        entry.box.setOutlineThickness(1.f);

        //material name on the right
        entry.nameText = makeText(m_font, defs[i].name, 12, sf::Color::White);
        entry.nameText.setPosition(
                startX + boxSize + 10.f,
                rowY + rowHeight / 2.f - 7.f
                );
        //count
        entry.countText = makeText(m_font, "x0", 12, sf::Color(180, 255, 180));
        entry.countText.setPosition(
                rightEdge - 24.f,
                rowY + rowHeight / 2.f - 7.f
                );

        m_materials.push_back(entry);
    }
}

// button
void Dialog::buildButton()
{
    // fronts from system
    if (!m_font.loadFromFile("assets/font.ttf"))
    {
        std::cerr << "Could not load font\n";
    }

    float buttonW = m_panelSize.x - 2 * m_padding;
    float buttonH = 40.f;

    //button below grid with a 20ps m_gap
    float buttonX = m_panelPos.x + m_padding;
    float buttonY = m_panelPos.y + m_panelSize.y - m_padding - buttonH;

    m_button.setSize(sf::Vector2f(buttonW, buttonH));
    m_button.setPosition(buttonX, buttonY);
    m_button.setFillColor(sf::Color(70, 140, 170));
    m_button.setOutlineColor(sf::Color(100, 180, 100));
    m_button.setOutlineThickness(1.f);

    m_buttonText = makeText(m_font, "Spawn", 22, sf::Color::White);
    centerTextIn(m_buttonText, sf::FloatRect(buttonX, buttonY, buttonW, buttonH));
    /*
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
    */
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

void Dialog::updateTabAppearance()
{
    for (int i = 0; i < 2; i++)
    {
        m_tabButtons[i].setFillColor(
                (i == m_activeTab)
                ? sf::Color(80, 80, 100) // active tab
                : sf::Color(50, 50, 60)
                );
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

int Dialog::getConfirmedTab() const 
{
    return m_confirmedTab;
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

const std::vector<MaterialEntry>& Dialog::getMaterials() const
{
    return m_materials;
}

void Dialog::resetMaterialsCount()
{
    for (auto& mat : m_materials)
    {
        mat.count = 0;
        mat.countText.setString("x0");
    }
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
        sf::Vector2f click(
                static_cast<float>(event.mouseButton.x),
                static_cast<float>(event.mouseButton.y)
                );

        //switch tabs
        for (int i = 0; i < 2; i++)
        {
            if (m_tabButtons[i].getGlobalBounds().contains(click))
            {
                m_activeTab = i;
                updateTabAppearance();
                return;
            }
        }
        // spawn btn
        if (m_button.getGlobalBounds().contains(click))
        {
            m_confirmedTab = m_activeTab;
            m_confirmed = true;
            m_isOpen = false;
            return;
        }

        //tab1
        if (m_activeTab == 0)
        {
            for (int i = 0; i < 9; i++)
            {
                if (m_cells[i].getGlobalBounds().contains(click))
                {
                    m_selected[i] = !m_selected[i];
                    updateCellColors();
                    return;
                }
            }
        }

        //tab2
        if (m_activeTab == 1)
        {
            for (auto& mat : m_materials)
            {
                if (mat.box.getGlobalBounds().contains(click))
                {
                    mat.count++;
                    mat.countText.setString("X" + std::to_string(mat.count));
                    return;
                }
            }
        }

        
    }
}


void Dialog::draw(sf::RenderWindow& window)
{
    if (!m_isOpen) return; // nothing bcs its closed

    window.draw(m_panel);

    for(int i = 0; i < 2; i++)
    {
        window.draw(m_tabButtons[i]);
        window.draw(m_tabLabels[i]);
    }

    if (m_activeTab == 0)
    {
        for (const auto& cell : m_cells)
            window.draw(cell);
    } else 
    {
        for (const auto& mat : m_materials)
        {
            window.draw(mat.box);
            window.draw(mat.nameText);
            window.draw(mat.countText);
        }
    }
        

    window.draw(m_button);
    window.draw(m_buttonText);
}













