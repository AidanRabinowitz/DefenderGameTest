#include "Laser.h"
#include <cmath>

Laser::Laser() : fired(false)
{
    shape.setSize(sf::Vector2f(15, 2));
    shape.setFillColor(sf::Color::Green);
    velocity.y = 0; // Laser should not need to move vertically
}

// In Laser::fire
void Laser::fire(sf::Vector2f playerPosition, sf::Vector2f mousePosition)
{
    shape.setPosition(playerPosition.x + 42, playerPosition.y);
    velocity.x = (mousePosition.x > playerPosition.x) ? LASER_SPEED : -LASER_SPEED;
    setFired(true);
}

void Laser::move()
{
    if (fired)
    {
        shape.move(velocity);
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
