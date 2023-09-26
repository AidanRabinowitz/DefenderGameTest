#include "Lander.h"
#include <iostream>
Lander::Lander()
    : destroyed(false)
{
    if (!landerTexture.loadFromFile("resources/landerShip.png"))
    {
        std::cerr << "Failed to load lander texture!" << std::endl;
    }
    landerSprite.setTexture(landerTexture);
    landerSprite.setScale(sf::Vector2f(0.1f, 0.1f));
    velocity = sf::Vector2f(0.0f, 0.0f);
}

void Lander::reset()
{
    destroyed = false;
}

void Lander::update()
{
    if (!destroyed)
    {
        // Move the lander
        landerSprite.move(0, LANDER_SPEED); // Adjust the speed as needed
    }
}

void Lander::render(sf::RenderWindow &window)
{
    // Render the lander on the window
    if (!destroyed)
    {
        window.draw(landerSprite);
    }
}

sf::Sprite &Lander::getSprite()
{
    return landerSprite;
}

bool Lander::isDestroyed() const
{
    return destroyed;
}
sf::Vector2f Lander::getPosition() const
{
    return landerSprite.getPosition();
}
void Lander::destroy()
{
    destroyed = true;
}

Humanoid *Lander::findNearestHumanoid(const std::vector<Humanoid> &humanoids) const
{
    if (humanoids.empty())
    {
        return nullptr;
    }

    Humanoid *nearestHumanoid = nullptr;
    float minDistance = std::numeric_limits<float>::max();

    for (const auto &humanoid : humanoids)
    {
        float distance = calculateDistance(getPosition(), humanoid.getPosition());
        if (distance < minDistance)
        {
            minDistance = distance;
            nearestHumanoid = const_cast<Humanoid *>(&humanoid);
        }
    }

    return nearestHumanoid;
}

float Lander::calculateDistance(const sf::Vector2f &point1, const sf::Vector2f &point2) const
{
    float dx = point1.x - point2.x;
    float dy = point1.y - point2.y;
    return std::sqrt(dx * dx + dy * dy);
}

float Lander::getDistance(const sf::Vector2f &targetPosition)
{
    // Calculate and return the Euclidean distance between the Lander's position and the target position
    sf::Vector2f currentPosition = landerSprite.getPosition();
    float dx = targetPosition.x - currentPosition.x;
    float dy = targetPosition.y - currentPosition.y;
    return std::sqrt(dx * dx + dy * dy);
}

void Lander::moveTowards(const sf::Vector2f &targetPosition)
{
    // Calculate the direction vector to move towards the target position
    sf::Vector2f currentPosition = landerSprite.getPosition();
    sf::Vector2f direction = targetPosition - currentPosition;

    // Normalize the direction vector (make it a unit vector)
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0)
    {
        direction /= length;
    }

    // Set the Lander's velocity based on the normalized direction vector
    // You may also need to adjust the speed here based on your game's requirements
    float speed = 2.0f; // Adjust this speed as needed

    velocity = direction * speed;

    // Update the Lander's position based on the velocity
    landerSprite.move(velocity);
}
void Lander::moveLanderUp()
{
    // Move the lander
    landerSprite.move(0, -2 * LANDER_SPEED); // Adjust the speed as needed
}

void Lander::attachToHumanoid(Humanoid *humanoid)
{
    attachedHumanoid = humanoid;
}

bool Lander::isAttached() const
{
    return attachedHumanoid != nullptr;
}

Humanoid *Lander::getAttachedHumanoid() const
{
    return attachedHumanoid;
}

bool Lander::wasDestroyedByLaser()
{
    return destroyed;
}