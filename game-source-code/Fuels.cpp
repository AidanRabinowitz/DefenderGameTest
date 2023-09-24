#include "Fuels.h"
#include "GameConstants.h" // Include any relevant constants

Fuels::Fuels()
    : destroyed(false)
{
    // Initialize 'destroyed' to false
    fuelsTexture.loadFromFile("resources/fuel.png");
    fuelsSprite.setTexture(fuelsTexture);
    fuelsSprite.setScale(sf::Vector2f(0.1f, 0.1f));
    // Set the initial position and other properties for the fuel
}
bool Fuels::checkCollision(const sf::FloatRect &playerBounds)
{
    // Check if the fuel sprite's bounds intersect with the player's bounds
    return fuelsSprite.getGlobalBounds().intersects(playerBounds);
}
void Fuels::update()
{
    // Update the position based on velocity, if needed
    // You can add collision detection logic here, e.g., check for collisions with other objects

    // Update the sprite's position
    fuelsSprite.setPosition(position);
}

void Fuels::render(sf::RenderWindow &window) const
{
    // Draw the fuel sprite
    window.draw(fuelsSprite);
}

// Inside Fuels class
bool Fuels::checkCollisionWithPlayer(const Player &player)
{
    if (fuelsSprite.getGlobalBounds().intersects(player.getGlobalBounds()))
    {
        // Collision with player detected
        destroy();
        return true;
    }
    return false;
}

bool Fuels::isDestroyed() const
{
    return destroyed;
}

void Fuels::destroy()
{
    destroyed = true;
}

sf::Vector2f Fuels::getPosition() const
{
    return fuelsSprite.getPosition();
}

void Fuels::setPosition(const sf::Vector2f &newPosition)
{
    position = newPosition;
    fuelsSprite.setPosition(position);
}

// Additional member functions specific to Fuels class, if needed
