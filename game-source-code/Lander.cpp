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
    // Set the initial position and other properties for the lander as needed
}

void Lander::reset()
{
    // Reset the lander's position and any other properties as needed
    destroyed = false;
}

void Lander::update()
{
    // Update the lander's position and behavior here
    if (!destroyed)
    {
        // Move the lander
        landerSprite.move(0, LANDER_SPEED); // Adjust the speed as needed
    }
    // You can add more logic for lander behavior here
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
// Implement the getPosition member function in the Lander class
sf::Vector2f Lander::getPosition() const
{
    return landerSprite.getPosition();
}
void Lander::destroy()
{
    destroyed = true;
    // Add any other logic for handling the destruction of the lander
}