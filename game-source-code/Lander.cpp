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
    // Set the initial position and other properties for the lander
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