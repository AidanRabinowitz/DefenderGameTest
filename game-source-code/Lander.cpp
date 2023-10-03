#include "Lander.h"
#include <iostream>
Lander::Lander(int id, std::vector<Humanoid> &humanoids)
    : id(id), humanoids(humanoids), destroyed(false), carryingHumanoid(false), onWayToTop(false), destroyedByLaser(false)
{
    landerTexture.loadFromFile("resources/landerShip.png");
    landerSprite.setTexture(landerTexture);
    landerSprite.setScale(sf::Vector2f(0.1f, 0.1f));
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

        if (id % 1 == 0)
        {
            if (!carryingHumanoid)
            {
                for (Humanoid &humanoid : humanoids)
                {
                    if (!humanoid.isCarried() && getSprite().getGlobalBounds().intersects(humanoid.humanoidSprite.getGlobalBounds()))
                    {
                        carryingHumanoid = true;
                        carriedHumanoid = &humanoid;
                        carriedHumanoid->setCarried(true);
                        std::cout << "carried" << std::endl;
                        onWayToTop = true;
                        break;
                    }
                }
            }
            else if (onWayToTop)
            {
                getSprite().move(0, -2 * LANDER_SPEED);
                carriedHumanoid->humanoidSprite.move(0, -LANDER_SPEED);

                if (getSprite().getPosition().y < 0)
                {
                    if (!carriedHumanoid->isTouchingPlayer())
                    {
                        // Lander is destroyed, set freeFall only for the carried humanoid
                        destroyed = true;
                        onWayToTop = false;
                        carriedHumanoid->destroy();
                    }
                    carriedHumanoid = nullptr; // Reset the carried humanoid
                    std::cout << "out of bounds" << std::endl;
                }
            }
        }
    }
    if (destroyed && carriedHumanoid != nullptr)
    {
        carriedHumanoid->setFreeFall(true); // Set freeFall for the carried humanoid
        carriedHumanoid = nullptr;          // Reset the carried humanoid
    }
}

bool Lander::isCarryingHumanoid() const
{
    return carryingHumanoid;
}

void Lander::releaseHumanoid()
{
    carryingHumanoid = false;
    carriedHumanoid = nullptr;
}

void Lander::setId(int id)
{
    this->id = id;
}
void Lander::moveAndCheckBounds()
{
    // Move the lander
    landerSprite.move(0, LANDER_SPEED); // Adjust the speed as needed

    // Check if the lander is out of bounds
    if (landerSprite.getPosition().y > WINDOW_HEIGHT)
    {
        destroyed = true; // Mark it as destroyed when out of bounds
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
