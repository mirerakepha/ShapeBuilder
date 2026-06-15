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

};
