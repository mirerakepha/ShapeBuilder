#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
    public: 
        Ball();
        void reset();
        void setActive(bool active);
        bool isActive() const; // if true then ball starts to move

        void update(float dt); //delta time
        void draw(sf::RenderWindow& window);

        sf::Vector2f getPosition() const;
        float getRadius() const;
    private:
        sf::CircleShape m_shape;
        sf::Vector2f m_velocity;
        bool m_active;

        static constexpr float RADIUS = 18.f;
        static constexpr float SPAWN_X = 60.f; // world postion
        static constexpr float SPAWN_Y = 60.f;


};

