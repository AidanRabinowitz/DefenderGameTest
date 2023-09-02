#include "EnemyMissile.h"
#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <iostream> // For debugging
#include <cmath>

EnemyMissile::EnemyMissile(sf::Vector2f startPosition, sf::Vector2f targetDirection)
    : velocity(5000.f), targetDirection(targetDirection)
{
    // Initialize the missile's position and appearance
    missileShape.setSize(sf::Vector2f(22.f, 22.f));
    missileShape.setFillColor(sf::Color::Green);
    missileShape.setPosition(startPosition);

    // Normalize the target direction vector
    float length = std::sqrt(targetDirection.x * targetDirection.x + targetDirection.y * targetDirection.y);
    if (length != 0)
    {
        targetDirection /= length;
    }
}

void EnemyMissile::update(float deltaTime)
{
    // Move the missile towards the target direction
    missileShape.move(velocity * targetDirection * deltaTime);
}

void EnemyMissile::draw(sf::RenderWindow &window) const
{
    window.draw(missileShape);
}
