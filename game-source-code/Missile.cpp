#include "Missile.h"
#include <cmath>
#define MISSILE_SPEED 4 // Replace with your desired speed

Missile::Missile(sf::Vector2f initialPosition, sf::Vector2f targetPosition) : target(targetPosition)
{
    shape.setSize(sf::Vector2f(3, 15));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(initialPosition); // Set the initial position here

    sf::Vector2f direction = target - shape.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    velocity.x = direction.x / length * MISSILE_SPEED;
    velocity.y = direction.y / length * MISSILE_SPEED;
}

void Missile::move()
{
    shape.move(velocity);
}

void Missile::draw(sf::RenderWindow &window)
{
    window.draw(shape);
}