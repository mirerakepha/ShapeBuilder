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
    result.hit = false;
    result.material = material;

    // find closest point on rectangle to ball center
    float closestX = std::max(rect.left,
                     std::min(ballCenter.x, rect.left + rect.width));
    float closestY = std::max(rect.top,
                     std::min(ballCenter.y, rect.top + rect.height));

    // distance from ball center to the closest point
    sf::Vector2f diff(
            ballCenter.x - closestX,
            ballCenter.y - closestY
            );
    float dist = length(diff);

    // collission happens if distance < radius
    if (dist < ballRadius && dist > 0.f)
    {
        result.hit = true;
        result.penetration = ballRadius - dist;
        // the direction we bush ball to
        result.normal = normalize(diff);
    } else if (dist == 0.f) {
        // ball center is exactly inside the rectangle
        result.hit = true;
        result.penetration = ballRadius;
        result.normal = sf::Vector2f(0.f, -1.f);
        
    }


    return result;
}

sf::Vector2f Physics::reflect(sf::Vector2f velocity,
        sf::Vector2f normal,
        float bounciness
        )
{
    // reflection () V' = v - 2(v.n)n
    float vDotN = dot(velocity, normal);
    sf::Vector2f reflected = velocity - normal * (2.f * vDotN);

    // bounciness
    return reflected * bounciness;
}
























