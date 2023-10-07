#pragma once
#include "Humanoid.h"
#include "GameConstants.h" // Include your game constants here
#include <cmath>
#include <limits>
#include <memory>

class Lander : public GameEntity
{
public:
    Lander(int id, std::vector<Humanoid> &humanoids);
    void moveAndCheckBounds();
    void setId(int id);
    void reset();
    void update();
    void render(sf::RenderWindow &window);
    bool isDestroyed() const;
    void destroy();
    bool isCarryingHumanoid() const;
    bool isMovingUp() const;

private:
    Humanoid *carriedHumanoid;
    sf::Clock spawnTimer;
    std::vector<Humanoid> &humanoids; // Reference to the humanoids container
    bool destroyedByLaser;
    bool carryingHumanoid;
    bool onWayToTop;
    bool destroyed;
    int id;
};