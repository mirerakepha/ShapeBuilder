#include "ShapeManager.hpp"
#include <cmath>
#include <stddef.h>


ShapeManager::ShapeManager()
    : m_dragIndex(-1)   // -1 means nothing is being dragged
{}

void ShapeManager::spawnBlock(const std::array<bool, 9>& pattern, sf::Vector2f center)
{
    m_dragIndex = -1; // reset drag state on new spawn

    //block at center 3x3 35px cells 2px gap
    float offset = (3 * 35.f + 2 * 2.f) / 2.f;

    sf::Vector2f anchor(center.x - offset, center.y - offset);
    m_blocks.emplace_back(pattern, anchor);
}


/*
bool ShapeManager::hitTest(const sf::CircleShape& circle, sf::Vector2f point)
{
    sf::Vector2f center = circle.getPosition();
    float radius = circle.getRadius();

    // pythagoras -> dist = sqrt((dx * dx) + (dy * dy))
    float dy = point.y - center.y;
    float dx = point.x - center.x;
    float distance = std::sqrt(dx*dx + dy*dy);

    // true if mouse is inside the radius
    return distance <= radius;
}
*/

void ShapeManager::handleEvent(const sf::Event& event, sf::Vector2f mousePos)
{
    // left click to  pick a circle
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        // top drwan circle gets picked up first
        for (int i = static_cast<int>(m_blocks.size()) -1; i >= 0; i--)
        {
            if (m_blocks[i].contains(mousePos))
            {
                m_dragIndex = i;
                //record offset so circle doesnt snap to cursor center
                m_dragOffset = m_blocks[i].getPosition() - mousePos;
                break; //only pick one circle at a time
            }
        }
        /*
        // if no circle was hit spawn a new one
        if (m_dragIndex == -1)
        {
            sf::CircleShape circle(30.f);
            circle.setFillColor(sf::Color(100, 180, 255));
            circle.setOutlineColor(sf::Color::White);
            circle.setOutlineThickness(1.f);
            circle.setOrigin(30.f, 30.f);
            circle.setPosition(mousePos);
            m_circles.push_back(circle);

        }
        */
    }

    // drop to release
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        m_dragIndex = -1; // drop
    }
}


void ShapeManager::spawnMaterialBlock(sf::Color color, sf::Vector2f center)
{
    /// a single square
    std::array<bool, 9> pattern{};
    pattern[4] = true; //

    m_dragIndex = -1;
    float offset = (3 * 35.f + 2 * 2.f) / 2.f;
    sf::Vector2f anchor(center.x - offset, center.y - offset);

    m_blocks.emplace_back(pattern, anchor, color);
}

void ShapeManager::update(sf::Vector2f mousePos)
{

    if (m_dragIndex < 0 || m_dragIndex >= static_cast<int>(m_blocks.size())) return;
    m_blocks[m_dragIndex].setPosition(mousePos + m_dragOffset);
    /*
    // drag a block
    if (m_dragIndex != -1)
    {
        m_blocks[m_dragIndex].setPosition(mousePos + m_dragOffset);
        //clamp the block inside the window
        sf::FloatRect bounds = m_blocks[m_dragIndex].getBounds();

        sf::Vector2f pos = m_blocks[m_dragIndex].getPosition();

        // window size
        float ww = static_cast<float>(windowSize.x);
        float wh = static_cast<float>(windowSize.y);

        // distance from anchor to edges
        float toLeft = pos.x - bounds.left;
        float toTop = pos.y - bounds.top;
        float toRight = (bounds.left - bounds.width) - pos.x;
        float toBottom = (bounds.top - bounds.height) - pos.y;

        // clamp such that none of the edges get out of the window
        if (bounds.left < 0)
            pos.x = toLeft;
        if (bounds.top < 0)
            pos.y = toTop;
        if (bounds.left + bounds.width > windowSize.x)
            pos.x = ww - toRight;
        if (bounds.top + bounds.height > windowSize.y)
            pos.y = wh - toBottom;

        m_blocks[m_dragIndex].setPosition(pos);
    }
    */
}

void ShapeManager::undo()
{
    if (!m_blocks.empty())
    {
        m_blocks.pop_back();
        m_dragIndex = -1; // reset incase we deleted the dragged block
    }

}

void ShapeManager::draw(sf::RenderWindow& window)
{
    for (auto& block : m_blocks)
        block.draw(window);
}


