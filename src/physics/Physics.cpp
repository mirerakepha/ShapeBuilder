#include "Physics.hpp"
#include <cmath>
#include <algorithm>

float Physics::dot(sf::Vector2f a, sf::Vector2f b)
{
    return a.x * b.x + a.y * b.y;
}

float Physics::length(sf::Vector2f v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

sf::Vector2f Physics::normalize(sf::Vector2f v)
{
    float len = length(v);
    if (len == 0.f) return sf::Vector2f(0.f, 0.f);
    return sf::Vector2f(v.x / len, v.y / len);
}

CollisionResult Physics::circleRect(
    sf::Vector2f ballCenter,
    float        ballRadius,
    sf::FloatRect rect,
    const std::string& material)
{
    CollisionResult result;
    result.hit = false;result.material = material;


    return result;
}
