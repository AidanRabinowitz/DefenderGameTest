// CollisionHandler.h
#pragma once
#include "Lander.h"
#include "Player.h"
#include "Missile.h"
#include "Laser.h"
#include "Humanoid.h"

class CollisionHandler
{
public:
    CollisionHandler() = default;

    // Handle collisions between lasers and landers
    void handleLaserLanderCollisions(std::vector<Laser> &lasers, std::vector<Lander> &landers, int &score);

    // Handle collisions between lasers and humanoids
    void handleLaserHumanoidCollisions(std::vector<Laser> &lasers, std::vector<Humanoid> &humanoids);

    // Handle collisions between player and landers
    bool handlePlayerLanderCollisions(const Player &player, const std::vector<Lander> &landers);

    // Handle collisions between player and missiles
    bool handlePlayerMissileCollisions(const Player &player, const std::vector<Missile> &missiles);
};
