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
//bool Laser::isTouching(const sf::FloatRect &bounds) const
//{
    // Add your collision detection logic here
    // For example, you can use sf::FloatRect::intersects or other collision detection methods.
    // Return true if there's a collision, otherwise return false.
    // You'll need to define how collision is determined based on your game's requirements.
//}

// In Laser::fire
void Laser::fire(sf::Vector2f startPosition, sf::Vector2f mousePosition)
{
    shape.setPosition(startPosition);
    fired = true;

    // Calculate the direction vector from the laser's position to the mouse position
    sf::Vector2f direction = mousePosition - startPosition;

    direction = mousePosition;

    // Set the velocity based on the direction vector
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
