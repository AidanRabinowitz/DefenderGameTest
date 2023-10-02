#include "humanoid.h"
#include "GameConstants.h"
Humanoid::Humanoid()
{
    // Initialize 'destroyed' to false
    humanoidTexture.loadFromFile("resources/humanoid.png");
    humanoidSprite.setTexture(humanoidTexture);
    humanoidSprite.setScale(sf::Vector2f(0.1f, 0.1f));
    destroyed = false;
    freeFall = false;
    // Set the initial position and other properties for the humanoid
}

void Humanoid::render(sf::RenderWindow &window) const
{
    // Draw the humanoid sprite
    window.draw(humanoidSprite);
}

void Humanoid::passengerMovement(float offsetX, float offsetY)
{
    humanoidSprite.move(offsetX, offsetY);
}

bool Humanoid::isTouchingPlayer()
{
    return touchingPlayer;
}

void Humanoid::update(const sf::Vector2f &playerPosition, const Player &player)
{
    if (freeFall && !touchingPlayer)
    {
        // Calculate the player's bounds
        sf::FloatRect playerBounds = sf::FloatRect(playerPosition.x, playerPosition.y, player.getGlobalBounds().width, player.getGlobalBounds().height);

        if (humanoidSprite.getGlobalBounds().intersects(playerBounds))
        {
            touchingPlayer = true;

            // Calculate the offset to position the humanoid relative to the player
            sf::Vector2f offset = sf::Vector2f(
                player.getPosition().x - humanoidSprite.getPosition().x,
                player.getPosition().y - humanoidSprite.getPosition().y);

            // Update the humanoid's position to follow the player
            humanoidSprite.setPosition(player.getPosition() - offset);
        }
        else
        {
            // Move the humanoid down (fall) when not touching the player
            humanoidSprite.move(0, LANDER_SPEED); // Adjust the speed as needed
        }
    }

    // Check if the humanoid is out of bounds (below the screen)
    if (humanoidSprite.getPosition().y > WINDOW_HEIGHT)
    {
        destroy(); // Mark the humanoid as destroyed
    }
}

bool Humanoid::isDestroyed() const
{
    return destroyed;
}
bool Humanoid::checkCollisionWithLaser(const Laser &laser) const
{
    return !destroyed && humanoidSprite.getGlobalBounds().intersects(laser.shape.getGlobalBounds());
}
// setPosition function to set the position of the humanoid
void Humanoid::setPosition(float x, float y)
{
    humanoidSprite.setPosition(x, y);
}

bool Humanoid::isCarried() const
{
    return carried;
}
void Humanoid::destroy()
{
    // Implement the destruction logic here
    destroyed = true;
}
void Humanoid::setCarried(bool carriedStatus)
{
    carried = carriedStatus;
}
void Humanoid::setFreeFall(bool fallStatus)
{
    freeFall = fallStatus;
    std::cout << "falling" << std::endl;
}
