#include "Player.h"
#include "GameConstants.h"
Player::Player()
{
    // Your existing constructor code
    playerTexture.loadFromFile("resources/playerShip.png");
    totalFuel = 100.0f;
    currentFuel = 100.0f;
    fuelConsumptionRate = 10.0f;
    playerSprite.setTexture(playerTexture);
    playerSprite.setScale(sf::Vector2f(0.1, 0.1));
    playerSprite.setPosition(WINDOW_WIDTH / 2 - 25, WINDOW_HEIGHT - 60);
    descending = false; // Initialize descending flag
}

void Player::consumeFuel(float deltaTime)
{
    if (!descending)
    {

        // Check for WASD key presses and consume fuel accordingly
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            float fuelToConsume = fuelConsumptionRate * deltaTime;
            if (currentFuel >= fuelToConsume)
            {
                currentFuel -= fuelToConsume;
            }
            else
            {
                currentFuel = 0.0f; // Ensure fuel doesn't go below zero
            }
        }
    }
}
void Player::resetCurrentFuel()
{
    currentFuel = 100.0f;
}
bool Player::hasFuel() const
{
    return currentFuel > 0;
}
float Player::getCurrentFuel() const
{
    return currentFuel;
}
float Player::getTotalFuel() const
{
    return totalFuel;
}

void Player::renderFuelBar(sf::RenderWindow &window) const
{
    // Calculate the fuel bar width based on the current fuel level and total fuel capacity
    float fuelBarWidth = (currentFuel / totalFuel) * 100; // Adjust FUEL_BAR_WIDTH as needed

    // Create and render the fuel bar rectangle (you may need to define a position)
    sf::RectangleShape fuelBar(sf::Vector2f(fuelBarWidth, 10)); // Adjust FUEL_BAR_HEIGHT as needed
    fuelBar.setFillColor(sf::Color::Green);                     // Adjust color as needed
    fuelBar.setPosition(WINDOW_WIDTH - 10, WINDOW_HEIGHT - 10); // Adjust position as needed
    window.draw(fuelBar);
}

void Player::setPosition(float x, float y)
{
    playerSprite.setPosition(x, y);
}

void Player::move(float offsetX, float offsetY)
{
    playerSprite.move(offsetX, offsetY);
}

void Player::setTexture(const sf::Texture &texture)
{
    playerSprite.setTexture(texture);
}

void Player::setScale(const sf::Vector2f &factors)
{
    playerSprite.setScale(factors);
}

void Player::render(sf::RenderWindow &window) const
{
    window.draw(playerSprite);
}

const sf::Vector2f &Player::getPosition() const
{
    return playerSprite.getPosition();
}

const sf::FloatRect Player::getGlobalBounds() const
{
    return playerSprite.getGlobalBounds();
}