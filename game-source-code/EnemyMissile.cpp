#include "EnemyMissile.h"

// Constructor
EnemyMissile::EnemyMissile(sf::Vector2f initialPosition, sf::Vector2f initialVelocity)
    : missileShape(10.0f) // Set the radius of the circle
{
    missileShape.setPosition(initialPosition);
    velocity = initialVelocity;
    alive = true;
}

// Destructor
EnemyMissile::~EnemyMissile()
{
    // Destructor implementation, if needed
}

// Update function to move and update the missile
void EnemyMissile::update(float deltaTime)
{
    if (alive)
    {
        missileShape.setPosition(missileShape.getPosition() + velocity * deltaTime);

        // Check if the missile is out of bounds or other conditions to set it as not alive
        // For example, you can add code here to check if the missile is out of the window bounds.
        // If it is, set alive to false.

        // Example condition to set the missile as not alive:
        // if (missileShape.getPosition().y > windowSize.y) {
        //     alive = false;
        // }
    }
}

// Function to check if the missile is alive
bool EnemyMissile::isAlive() const
{
    return alive;
}

// Function to get the position of the missile
sf::Vector2f EnemyMissile::getPosition() const
{
    return missileShape.getPosition();
}

// Function to draw the missile
void EnemyMissile::draw(sf::RenderWindow &window)
{
    if (alive)
    {
        window.draw(missileShape);
    }
}
