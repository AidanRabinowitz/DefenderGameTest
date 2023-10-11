#include "Lander.h"
#include <iostream>
Lander::Lander(int id, std::vector<Humanoid> &humanoids)
    : id(id), humanoids(humanoids), destroyed(false), carryingHumanoid(false), onWayToTop(false), destroyedByLaser(false), spawnTimer(spawnTimer)
{
    texture.loadFromFile("resources/landerShip.png");
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(0.1f, 0.1f));
    velocity = sf::Vector2f(0.0f, 0.0f);
}
int Humanoid::humansKilled = 0; // Initialize the static variable

void Lander::reset()
{
    destroyed = false;
}

void Lander::update()
{
    if (!destroyed)
    {
        moveAndCheckBounds();

        if (id % 1 == 0) // Used to set the frequency of landers picking up humanoids. Currently, every lander can pick up humanoids.
        {
            if (!carryingHumanoid)
            {
                for (Humanoid &humanoid : humanoids)
                {
                    if (!humanoid.isCarried() && sprite.getGlobalBounds().intersects(humanoid.sprite.getGlobalBounds()))
                    {
                        carryingHumanoid = true;
                        carriedHumanoid = &humanoid;
                        carriedHumanoid->setCarried(true);
                        onWayToTop = true;
                        break;
                    }
                }
            }
            else if (onWayToTop)
            {
                sprite.move(0, -2 * LANDER_SPEED);
                carriedHumanoid->sprite.move(0, -LANDER_SPEED);

                if (sprite.getPosition().y < 0)
                {
                    if (!carriedHumanoid->isTouchingPlayer())
                    {
                        // Lander is destroyed, set freeFall only for the carried humanoid
                        destroyed = true;
                        onWayToTop = false;
                        carriedHumanoid->destroy();
                    }
                    carriedHumanoid = nullptr; // Reset the carried humanoid
                }
            }
        }
    }
    if (isDestroyed() && carriedHumanoid != nullptr && isCarryingHumanoid())
    {
        carriedHumanoid->setFreeFall(true); // Set freeFall for the carried humanoid
        carriedHumanoid = nullptr;          // Reset the carried humanoid
    }
}

bool Lander::isMovingUp() const
{
    return onWayToTop;
}

bool Lander::isCarryingHumanoid() const
{
    return carryingHumanoid;
}

void Lander::setId(int id)
{
    this->id = id;
}
void Lander::moveAndCheckBounds()
{
    // Move the lander
    sprite.move(0, LANDER_SPEED); // Adjust the speed as needed

    // Check if the lander is out of bounds
    if (sprite.getPosition().y > WINDOW_HEIGHT)
    {
        destroyed = true; // Mark it as destroyed when out of bounds
    }
}

void Lander::render(sf::RenderWindow &window)
{
    // Render the lander on the window
    if (!destroyed)
    {
        window.draw(sprite);
    }
}

bool Lander::isDestroyed() const
{
    return destroyed;
}

void Lander::destroy()
{
    destroyed = true;
}