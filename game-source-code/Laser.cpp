#include "Laser.h"
#include <cmath>
#define LASER_SPEED 10 // Replace with your desired speed

Laser::Laser() : fired(false)
{
    shape.setSize(sf::Vector2f(3, 15));
    shape.setFillColor(sf::Color::Green);
    velocity.x = LASER_SPEED;
    velocity.y = 0; // Laser should not move vertically
}

// In Laser::fire
void Laser::fire(sf::Vector2f startPosition, sf::Vector2f mousePosition)
{
    shape.setPosition(startPosition);
    fired = true;

    // Calculate the direction vector from the laser's position to the mouse position
    sf::Vector2f direction = mousePosition - startPosition;

    // Normalize the direction vector (convert it to a unit vector)
    direction = mousePosition;

    // Set the velocity based on the direction vector, casting LASER_SPEED to float
    velocity = direction * static_cast<float>(LASER_SPEED);

    // Adjust the laser's rotation if needed (e.g., using shape.setRotation())
}

void Laser::move()
{
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
