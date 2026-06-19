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


void ShapeManager::spawnMaterialBlock(sf::Color color, sf::Vector2f center, const std::string& material)
{
    /// a single square
    std::array<bool, 9> pattern{};
    pattern[4] = true; //

    m_dragIndex = -1;
    float offset = (3 * 35.f + 2 * 2.f) / 2.f;
    sf::Vector2f anchor(center.x - offset, center.y - offset);

    m_blocks.emplace_back(pattern, anchor, color, material);
}

void ShapeManager::update(sf::Vector2f mousePos)
{

    if (m_dragIndex < 0 || m_dragIndex >= static_cast<int>(m_blocks.size())) return;
    m_blocks[m_dragIndex].setPosition(mousePos + m_dragOffset);
   
}

void ShapeManager::resolveCollisions(Ball& ball, AudioManager& audio)
{
    if (!ball.isActive()) return;

    sf::Vector2f ballPos = ball.getPosition();
    float ballRadius = ball.getRadius();
    sf::Vector2f velocity = ball.getVelocity();

    bool hitThisFrame = false;

    for (auto& block : m_blocks)
    {
        for (const auto& cellRect : block.getCellBounds())
        {
            CollisionResult result = Physics::circleRect(
                    ballPos, ballRadius, cellRect, block.getMaterial()
                    );
            if (result.hit)
            {
                // push ball out of surface so it doesnt sink in
                ball.move(result.normal * result.penetration);

                // ball pos after push
                ballPos = ball.getPosition();

                // reflect velocity >> bounciness varies by material
                float bounciness = 0.75f;
                if (result.material == "Steel") bounciness = 0.9f;
                else if (result.material == "Wood") bounciness = 0.60f; 
                else if (result.material == "Plastic") bounciness = 0.70f; 
                else if (result.material == "Glass") bounciness = 0.85f; 
                else if (result.material == "Iron") bounciness = 0.50f;

                velocity = Physics::reflect(velocity, result.normal, bounciness);

                // onlyplay sound once per frame if hitting multiple cells
                if (!hitThisFrame)
                {
                    if (result.material.empty())
                        audio.playDefaultBounce();
                    else 
                        audio.playBounce(result.material);

                    hitThisFrame = true;
                }
            }
        }
    }
    ball.setVelocity(velocity);
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


