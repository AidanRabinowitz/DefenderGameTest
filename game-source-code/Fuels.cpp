#include "Fuels.h"
#include "GameConstants.h" // Include any relevant constants

Fuels::Fuels()
    : destroyed(false)
{
    // Initialize 'destroyed' to false
    texture.loadFromFile("resources/fuel.png");
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(0.1f, 0.1f));
    // Set the initial position and other properties for the fuel
}

void Fuels::spawnFuel(std::vector<Fuels> &fuels, const sf::Texture &texture)
{
    Fuels fuelCan;

    // Set the fuel's position to a random location along the X-axis
    float xPos = static_cast<float>(rand() % static_cast<int>(WINDOW_WIDTH - fuelCan.sprite.getGlobalBounds().width));
    fuelCan.sprite.setPosition(sf::Vector2f(xPos, WINDOW_HEIGHT - fuelCan.sprite.getGlobalBounds().height));

    fuelCan.sprite.setTexture(texture);
    fuels.push_back(fuelCan);
}

bool Fuels::checkCollision(const sf::FloatRect &playerBounds)
{
    // Check if the fuel sprite's bounds intersect with the player's bounds
    return sprite.getGlobalBounds().intersects(playerBounds);
}
void Fuels::update()
{
    // Update the sprite's position
    sprite.setPosition(position);
}

void Fuels::render(sf::RenderWindow &window) const
{
    // Draw the fuel sprite
    window.draw(sprite);
}

// Inside Fuels class
bool Fuels::checkCollisionWithPlayer(const Player &player)
{
    if (sprite.getGlobalBounds().intersects(player.getGlobalBounds()))
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

void Fuels::setPosition(const sf::Vector2f &newPosition)
{
    position = newPosition;
    sprite.setPosition(position);
}