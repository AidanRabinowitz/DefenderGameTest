#include "Lander.h"
#include "Missile.h"
#include "GameConstants.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib> // for rand

// Define the missing constants
#define MISSILE_INTERVAL 1000  // Fire a missile every 1 second
std::vector<Missile> missiles; // Definition of the 'missiles' vector

Lander::Lander(const sf::Vector2f &playerPos) : destroyed(false), playerPosition(playerPos)
{

    shape.setSize(sf::Vector2f(30, 30));
    shape.setFillColor(sf::Color::Red);
    // Set the spawn position to a random position away from the player
    spawnPosition = sf::Vector2f(rand() % (WINDOW_WIDTH - 30), -30);
    shape.setPosition(spawnPosition);
    velocity.x = LANDER_SPEED;
    velocity.y = LANDER_SPEED;
    fireRateClock.restart(); // Initialize the fire rate clock
}

void Lander::spawn(sf::RenderWindow &window, std::vector<Lander> &landers)
{
    Lander lander(playerPosition);
    lander.shape.setSize(sf::Vector2f(30, 30));
    lander.shape.setFillColor(sf::Color::Red);
    lander.shape.setPosition(rand() % (WINDOW_WIDTH - 30), 0);
    lander.velocity.x = LANDER_SPEED;
    lander.velocity.y = LANDER_SPEED;
    lander.isDestroyed() = false;
    landers.push_back(lander);
}

sf::Vector2f Lander::getSpawnPosition() const
{
    return spawnPosition;
}

// Define the missing variables
sf::Vector2f playerPosition; // Assuming you have a player position variable

void Lander::move()
{
    // Set a constant horizontal velocity for leftward movement
    velocity.x = -LANDER_SPEED; // Adjust LANDER_SPEED as needed

    // Update the position of the lander based on its velocity
    shape.move(velocity);

    // Fire missiles at the specified fire rate
    // Fire missiles at the specified fire rate towards the player's position
    if (fireRateClock.getElapsedTime().asMilliseconds() > MISSILE_INTERVAL)
    {
        missiles.push_back(Missile(shape.getPosition(), playerPosition));
        fireRateClock.restart(); // Reset the fire rate timer
    }

    // You can add additional logic here to handle screen boundaries or other behaviors
}

void Lander::draw(sf::RenderWindow &window)
{
    if (!destroyed)
    {
        window.draw(shape);
    }
}

bool &Lander::isDestroyed()
{
    return destroyed;
}

const bool &Lander::isDestroyed() const
{
    return destroyed;
}

void Lander::destroy()
{
    destroyed = true;
}
