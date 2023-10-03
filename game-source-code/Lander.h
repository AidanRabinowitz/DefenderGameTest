#pragma once
#include "Humanoid.h"
#include <SFML/Graphics.hpp>
#include "GameConstants.h" // Include your game constants here
#include <cmath>
#include <limits>
#include <memory>
class Lander
{
public:
    Lander(int id, std::vector<Humanoid> &humanoids);
    void moveAndCheckBounds();
    void setId(int id);

    void reset();
    void update();
    void render(sf::RenderWindow &window);
    sf::Vector2f getPosition() const;
    sf::Sprite &getSprite();

    bool isDestroyed() const;
    sf::Sprite landerSprite;
    sf::Texture landerTexture;
    void destroy();
    void releaseHumanoid();
    bool isCarryingHumanoid() const;
    Humanoid *carriedHumanoid;

private:
    std::vector<Humanoid> &humanoids; // Reference to the humanoids container
    bool destroyedByLaser;
    sf::Vector2f velocity;
    bool carryingHumanoid;
    bool onWayToTop;
    bool destroyed;
    int id;
};
