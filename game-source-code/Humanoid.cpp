#include "humanoid.h"
#include "GameConstants.h"

Humanoid::Humanoid()
{
    // Initialize 'destroyed' to false
    texture.loadFromFile("resources/humanoid.png");
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(0.1f, 0.1f));
    destroyed = false;
    freeFall = false;
    touchingPlayer = false;
    humansKilled = 0;
    carried = false; // Initialize the carried flag
}

void Humanoid::reset()
{
    // Reset the position to the original position defined in the constructor
    setPosition(originalPosition.x, originalPosition.y);

    // Reset any other flags or properties to their initial state
    freeFall = false;
    touchingPlayer = false;
    carried = false;
}

void Humanoid::passengerMovement(float offsetX, float offsetY)
{
    sprite.move(offsetX, offsetY);
}

bool Humanoid::isTouchingPlayer()
{
    return touchingPlayer;
}

void Humanoid::update(const sf::Vector2f &playerPosition, const Player &player, const sf::RenderWindow &window)
{
    if (isTouchingPlayer())
    {
        // Apply passenger movement if touching the player during freefall
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && playerPosition.x > 0)
        {
            passengerMovement(-PLAYER_SPEED, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && playerPosition.x < window.getSize().x - 50)
        {
            passengerMovement(PLAYER_SPEED, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && playerPosition.y > 0)
        {
            passengerMovement(0, -PLAYER_SPEED);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && playerPosition.y < window.getSize().y - 50)
        {
            passengerMovement(0, PLAYER_SPEED);
        }
        if (playerPosition.y >= window.getSize().y - 50)
        {
            // Reset the humanoid to its original position
            reset();
        }
        
    }

    if (freeFall && !touchingPlayer)
    {
        // Calculate the player's bounds
        sf::FloatRect playerBounds = sf::FloatRect(playerPosition.x, playerPosition.y, player.getGlobalBounds().width, player.getGlobalBounds().height);

        if (sprite.getGlobalBounds().intersects(playerBounds))
        {
            touchingPlayer = true;

            // Calculate the offset to position the humanoid relative to the player
            sf::Vector2f offset = sf::Vector2f(
                player.getPosition().x - sprite.getPosition().x,
                player.getPosition().y - sprite.getPosition().y);

            // Update the humanoid's position to follow the player
            sprite.setPosition(player.getPosition() - offset);

            // Check if the humanoid is close to the ground
            if (sprite.getPosition().y >= WINDOW_HEIGHT - 5)
            {
                // Reset the humanoid to its original position
                reset();
            }
        }
        else
        {
            // Move the humanoid down (fall) when not touching the player
            sprite.move(0, LANDER_SPEED); // Adjust the speed as needed
        }
    }

    // Check if the humanoid is out of bounds (below the screen)
    if (sprite.getPosition().y > WINDOW_HEIGHT && !isTouchingPlayer())
    {
        destroy(); // Mark the humanoid as destroyed
    }
}

void Humanoid::setOriginalPosition(float x, float y)
{
    originalPosition = sf::Vector2f(x, y);
    setPosition(x, y); // Update the sprite's position here
}

void Humanoid::removeDestroyed(std::vector<Humanoid> &humanoids)
{
    humanoids.erase(std::remove_if(humanoids.begin(), humanoids.end(), [](const Humanoid &humanoid)
                                   { return humanoid.isDestroyed(); }),
                    humanoids.end());
}

bool Humanoid::isDestroyed() const
{
    return destroyed;
}
bool Humanoid::isFreeFall() const
{
    return freeFall;
}
bool Humanoid::checkCollisionWithLaser(const Laser &laser) const
{
    return !destroyed && sprite.getGlobalBounds().intersects(laser.shape.getGlobalBounds());
}
// setPosition function to set the position of the humanoid
void Humanoid::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

bool Humanoid::isCarried() const
{
    return carried;
}
void Humanoid::destroy()
{
    // Implement the destruction logic here
    humansKilled++;
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