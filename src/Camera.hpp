#pragma once
#include <SFML/Graphics.hpp>

class Camera
{
    public:
        Camera(sf::Vector2u windowSize);

        void handleEvent(const sf::Event& event);
        void update();

        // call before drawing world objects
        void applyWorldView(sf::RenderWindow& window);
        
        // call befire drawing ui
        void applyUIView(sf::RenderWindow& window);

        // convert screen coordinates to world px
        sf::Vector2f screenToWorld(
                sf::RenderWindow& window,
                sf::Vector2i screenPos
                ) const;
        sf::Vector2f getOffset() const;
    private:
        sf::View m_worldView; // moves with Camera
        sf::View m_uiView; // fixed covers the window
        sf::Vector2f m_offset; // how far from origin
        float m_panSpeed;
};
