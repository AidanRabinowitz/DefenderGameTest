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
    missileFireTimer.restart();
    // shape.setSize(sf::Vector2f(30, 30));
    // shape.setFillColor(sf::Color::Red);
    // Set the spawn position to a random position away from the player
    spawnPosition = sf::Vector2f(rand() % (WINDOW_WIDTH - 30), -30);
    landerSprite.setPosition(spawnPosition);
    velocity.x = LANDER_SPEED;
    velocity.y = LANDER_SPEED;
    fireRateClock.restart(); // Initialize the fire rate clock
    landerTexture.loadFromFile("resources/landerShip.png");
    landerSprite.setTexture(landerTexture);
    landerSprite.scale(sf::Vector2f(0.1, 0.1));
}

void Lander::spawn(sf::RenderWindow &window, std::vector<Lander> &landers)
{
    Lander lander(playerPosition);
    // lander.shape.setSize(sf::Vector2f(30, 30));
    // lander.shape.setFillColor(sf::Color::Red);
    lander.landerSprite.setPosition(rand() % (WINDOW_WIDTH - 30), 0);
    // texture.loadFromFile("resources/landerShip.png");
    // landerSprite.setTexture(texture);
    // landerSprite.scale(sf::Vector2f(0.1, 0.1));
    lander.velocity.x = LANDER_SPEED;
    lander.velocity.y = LANDER_SPEED;
    lander.isDestroyed() = false;
    landers.push_back(lander);
}

sf::Vector2f Lander::getPosition() const
{
    return landerSprite.getPosition(); // Return the current position of the lander
}

// Define the missing variables
sf::Vector2f playerPosition; // Assuming you have a player position variable

void Lander::move()
{
    // Set a constant horizontal velocity for leftward movement
    if (missileFireTimer.getElapsedTime().asMilliseconds() > MISSILE_INTERVAL)
    {
        missiles.push_back(Missile(landerSprite.getPosition(), playerPosition)); // Pass the lander's position as initial position
        missileFireTimer.restart();                                              // Reset the fire rate timer
    }
    velocity.y = -LANDER_SPEED; // Adjust LANDER_SPEED as needed

    // Update the position of the lander based on its velocity
    landerSprite.move(velocity);

    // Fire missiles at the specified fire rate
    // Fire missiles at the specified fire rate towards the player's position
    if (missileFireTimer.getElapsedTime().asMilliseconds() > MISSILE_INTERVAL)
    {
        missiles.push_back(Missile(landerSprite.getPosition(), playerPosition));
        missileFireTimer.restart(); // Reset the fire rate timer
    }

    // You can add additional logic here to handle screen boundaries or other behaviors
}

void Lander::draw(sf::RenderWindow &window)
{
    if (!destroyed)
    {
        window.draw(landerSprite);
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