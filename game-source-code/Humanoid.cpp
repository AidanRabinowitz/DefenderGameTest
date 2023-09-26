#include "humanoid.h"
#include "GameConstants.h"
Humanoid::Humanoid()
    : destroyed(false)
{
    // Initialize 'destroyed' to false
    humanoidTexture.loadFromFile("resources/humanoid.png");
    humanoidSprite.setTexture(humanoidTexture);
    humanoidSprite.setScale(sf::Vector2f(0.1f, 0.1f));
    // Set the initial position and other properties for the humanoid
}

void Humanoid::update()
{
    // Update the position based on velocity
    position += velocity;

    // You can add collision detection logic here, e.g., check for collisions with humanoids or the ground.

    // Update the sprite's position
    humanoidSprite.setPosition(position);
}

void Humanoid::render(sf::RenderWindow &window) const
{
    // Draw the humanoid sprite
    window.draw(humanoidSprite);
}

bool Humanoid::isTouching(const sf::FloatRect &bounds)
{
    // Check if the humanoid's sprite is touching the given bounds (e.g., humanoid's bounding box, player's bounding box)
    return humanoidSprite.getGlobalBounds().intersects(bounds);
}

bool Humanoid::isAttached() const
{
    return attached;
}

void Humanoid::setAttached(bool value)
{
    attached = value;
}

bool Humanoid::isDestroyed() const
{
    return destroyed;
}

void Humanoid::destroy()
{
    destroyed = true;
}

sf::Vector2f Humanoid::getPosition() const
{
    return humanoidSprite.getPosition();
}

void Humanoid::setPosition(const sf::Vector2f &newPosition)
{
    position = newPosition;
    humanoidSprite.setPosition(position);
}

void Humanoid::moveHumanoid(float speed)
{
    // Move the lander
    humanoidSprite.move(0, speed); // Adjust the speed as needed
}
void Humanoid::moveHumanoidDown()
{
    // Move the lander
    humanoidSprite.move(0, LANDER_SPEED); // Adjust the speed as needed
}

sf::Sprite &Humanoid::getSprite()
{
    return humanoidSprite;
}

void Humanoid::fall(float deltaTime, float gravity)
{
    // Calculate the new vertical position based on gravity and time
    float newY = position.y + (gravity * deltaTime);

    // Update the position and sprite
    position.y = newY;
    humanoidSprite.setPosition(position);
}
