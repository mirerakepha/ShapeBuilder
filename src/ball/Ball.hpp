#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
    public: 
        Ball();
        void reset();
        void set_active(bool active);
        void is_active() const; // if true then ball starts to move

        void update(float dt); //delta time
        void draw(sf::RenderWindow& window);

        sf::Vector2f getPosition() const;
        float getRadius() const;
    private:
        sf::CiicleShape m_shape;
        sf::Vector2f velocity;
        bool m_active;

        static constexpr float RADIUS = 18.f;
        static constexpr float SPAWN_X = 60.f; // world postion
        static constexpr float SPAWN_Y = 60.f;


}

