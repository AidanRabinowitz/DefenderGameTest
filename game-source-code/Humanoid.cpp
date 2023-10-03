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
    touchingPlayer = false;
}

void Humanoid::reset()
{
    // Reset the position to the original position defined in the constructor
    setPosition(originalPosition.x, originalPosition.y);

    // Reset any other flags or properties to their initial state
    freeFall = false;
    touchingPlayer = false;
    carried = false;
    // Reset any other properties as needed
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

            // Check if the humanoid is close to the ground
            if (humanoidSprite.getPosition().y >= WINDOW_HEIGHT - 5)
            {
                // Reset the humanoid to its original position
                reset();
            }
        }
        else
        {
            // Move the humanoid down (fall) when not touching the player
            humanoidSprite.move(0, LANDER_SPEED); // Adjust the speed as needed
        }
    }

    // Check if the humanoid is out of bounds (below the screen)
    if (humanoidSprite.getPosition().y > WINDOW_HEIGHT && !isTouchingPlayer())
    {
        destroy(); // Mark the humanoid as destroyed
    }
}

void Humanoid::setOriginalPosition(float x, float y)
{
    originalPosition = sf::Vector2f(x, y);
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