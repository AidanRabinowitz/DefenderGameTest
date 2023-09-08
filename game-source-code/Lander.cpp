#include "Lander.h"
#include <cstdlib> // for rand

#define WINDOW_WIDTH 800 // Replace with your actual window width
#define LANDER_SPEED 5   // Replace with your desired speed

Lander::Lander() : destroyed(false)
{
    shape.setSize(sf::Vector2f(30, 30));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(rand() % (WINDOW_WIDTH - 30), 0);
    velocity.x = LANDER_SPEED;
    velocity.y = LANDER_SPEED;
}

void Lander::spawn(sf::RenderWindow &window, std::vector<Lander> &landers)
{
    Lander lander;
    lander.shape.setSize(sf::Vector2f(30, 30));
    lander.shape.setFillColor(sf::Color::Red);
    lander.shape.setPosition(rand() % (WINDOW_WIDTH - 30), 0);
    lander.velocity.x = LANDER_SPEED;
    lander.velocity.y = LANDER_SPEED;
    lander.isDestroyed() = false;
    landers.push_back(lander);
}

void Lander::move()
{
    // Add your movement logic here
    // Example:
    shape.move(velocity);
}

void Lander::draw(sf::RenderWindow &window)
{
    if (!destroyed)
    {
        window.draw(shape);
    }
}

bool &Lander::isDestroyed()
{
    return destroyed;
}

const bool &Lander::isDestroyed() const
{
    return destroyed;
}

void Lander::destroy()
{
    destroyed = true;
}
