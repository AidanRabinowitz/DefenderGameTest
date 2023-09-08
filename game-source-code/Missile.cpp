#include "Missile.h"
#include <cmath>
#define MISSILE_SPEED 8 // Replace with your desired speed

Missile::Missile(const sf::Vector2f &position, const sf::Vector2f &target)
{
    shape.setSize(sf::Vector2f(5, 20));
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(position.x + 12, position.y + 30);

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
