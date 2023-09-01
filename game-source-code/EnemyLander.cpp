#include "EnemyLander.h"
#include "EnemyMissile.h"
#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream> // For debugging
#include <cmath>
#include <cstdlib> // Include this for rand()

EnemyLander::EnemyLander(sf::Vector2f position)
    : minDistance(100.f), fireCooldown(2.0f), fireTimer(0.0f), velocity(0.f, 0.f), movingUp(true) // Initialize velocity and movingUp
{
    // Initialize the position with the given position
    landerShape.setSize(sf::Vector2f(30.f, 30.f));
    landerShape.setFillColor(sf::Color::Red);
    landerShape.setPosition(position);

    // Initialize velocity with random values
    velocity.x = static_cast<float>(rand()) / RAND_MAX * 100.f - 50.f; // Random horizontal velocity
    velocity.y = static_cast<float>(rand()) / RAND_MAX * 100.f - 50.f; // Random vertical velocity
}

void EnemyLander::update(float deltaTime, sf::Vector2f playerShipPosition, std::vector<EnemyMissile> &missiles)
{
    if (movingUp && landerShape.getPosition().y <= 0.f)
    {
        movingUp = false;
    }
    else if (!movingUp && landerShape.getPosition().y >= 600.f)
    {
        movingUp = true;
    }

    if (movingUp)
    {
        landerShape.move(sf::Vector2f(0.f, -velocity.y * deltaTime)); // Move up
    }
    else
    {
        landerShape.move(sf::Vector2f(0.f, velocity.y * deltaTime)); // Move down
    }

    fireTimer += deltaTime;
    if (fireTimer >= fireCooldown)
    {
        // Fire a missile towards the player's ship
        sf::Vector2f targetPosition = playerShipPosition; // Update this with your target logic
        missileFire(targetPosition, missiles);
        fireTimer = 0.0f; // Reset the timer
    }
}

void EnemyLander::draw(sf::RenderWindow &window) const
{
    window.draw(landerShape);
}

void EnemyLander::missileFire(const sf::Vector2f &targetPosition, std::vector<EnemyMissile> &missiles)
{
    // Create a missile instance and pass it the target position
    EnemyMissile missile(landerShape.getPosition(), targetPosition);

    // Add the missile to the vector
    missiles.push_back(missile);
}
