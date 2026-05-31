#include "Block.hpp"
#include <stddef.h>
#include <limits>


Block::Block(const std::array<bool, 9>& pattern, sf::Vector2f anchor)
    : m_anchor(anchor),
    m_cellSize(35.f) //ecah square 35x35 px
{
    float gap = 2.f; // small gap btn squares

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            int index = row * 3 + col;

            if (!pattern[index]) continue; // skip unselected cells

            Cell cell;

            // local offset: where a square sits relatively to the anchor
            cell.localOffset = sf::Vector2f(
                    col * (m_cellSize + gap),
                    row * (m_cellSize + gap)
                    );
            cell.shape.setSize(sf::Vector2f(m_cellSize, m_cellSize));
            cell.shape.setFillColor(sf::Color(100, 200, 255));
            cell.shape.setOutlineColor(sf::Color(255, 255, 255));
            cell.shape.setOutlineThickness(1.f);
            // world pos == anchor + local offset
            cell.shape.setPosition(m_anchor + cell.localOffset);

            m_cells.push_back(cell);
        }
    }
}


void Block::setPosition(sf::Vector2f pos)
{
    m_anchor = pos;
    // update every squeare world pos
    for (auto& cell : m_cells)
        cell.shape.setPosition(m_anchor + cell.localOffset);
}


sf::Vector2f Block::getPosition() const
{
    return m_anchor;
}

sf::FloatRect Block::getBounds() const
{
    if (m_cells.empty())
        return sf::FloatRect(m_anchor.x, m_anchor.y, 0.f, 0.f);

    // start with extreme values then shrink to fit
    float left = std::numeric_limits<float>::max();
    float right = -std::numeric_limits<float>::max();
    float top = std::numeric_limits<float>::max();
    float bottom = -std::numeric_limits<float>::max();

    for (const auto& cell : m_cells)
    {
        sf::FloatRect b = cell.shape.getGlobalBounds();
        left = std::min(left, b.left);
        right = std::max(right, b.left + b.width);
        top = std::min(top, b.top);
        bottom = std::max(bottom, b.top + b.height);
    }
    return sf::FloatRect(left, top, right - left, bottom - top);
}


bool Block::contains(sf::Vector2f point) const
{
    // check if point is inside any of the squares
    for (const auto& cell : m_cells)
    {
        if (cell.shape.getGlobalBounds().contains(point))
            return true;

    }
    return false;
}


void Block::draw(sf::RenderWindow& window)
{
    for (const auto& cell : m_cells)
        window.draw(cell.shape);
}
