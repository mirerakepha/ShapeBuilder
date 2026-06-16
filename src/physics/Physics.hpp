#pragma once
#include <SFML/Graphics.hpp>
#include <string>


/// result collission
struct CollisionResult
{
    bool hit; // collission happen?
    sf::Vector2f normal; // direction to push ball out
    float penetration; // how deep trhe ball sank in
    std::string material; // which material was hit
};

class Physics
{
    public:
        // check ball circle against one rectangle cell
        static CollisionResult circleRect(
                sf::Vector2f ballCenter,
                float ballRadius,
                sf::FloatRect rect,
                const std::string& material
                );

        // reflects a velocity vector along a normal
        static sf::Vector2f reflect(
                sf::Vector2f velocity,
                sf::Vector2f normal,
                float bounciness = 0.75f
                );
        // dot product measures alignment of 2 vectors
        static float dot(sf::Vector2f a, sf::Vector2f b);

        //len of vector
        static float length(sf::Vector2f v);

        // normalizes a vector
        static sf::Vector2f normalize(sf::Vector2f v);
};
