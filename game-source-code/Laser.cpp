#include "Laser.h"

#define LASER_SPEED 10 // Replace with your desired speed

Laser::Laser() : fired(false)
{
    shape.setSize(sf::Vector2f(3, 15));
    shape.setFillColor(sf::Color::Green);
    velocity.x = LASER_SPEED;
    velocity.y = 0; // Laser should not move vertically
}

void Laser::fire(sf::Vector2f startPosition)
{
    shape.setPosition(startPosition);
    fired = true;
}

void Laser::move()
{
    // Add your movement logic here
    // Example:
    if (fired)
    {
        shape.move(velocity);
    }
}

void Laser::draw(sf::RenderWindow &window)
{
    if (fired)
    {
        window.draw(shape);
    }
}

bool Laser::isFired() const
{
    return fired;
}

void Laser::setFired(bool firedStatus)
{
    fired = firedStatus;
}
