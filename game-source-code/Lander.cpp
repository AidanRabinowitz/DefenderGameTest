#include "Lander.h"
#include "Humanoid.h"
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
    // Set the initial position and other properties for the lander
}

sf::Vector2f Lander::getVelocity() const
{
    return velocity;
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

void Lander::attachHumanoid(Humanoid *humanoid)
{
    abductedHumanoid = humanoid;
}

bool Lander::isCarryingHumanoid() const
{
    return abductedHumanoid != nullptr;
}

Humanoid* Lander::getAbductedHumanoid() const
{
    return abductedHumanoid;
}
