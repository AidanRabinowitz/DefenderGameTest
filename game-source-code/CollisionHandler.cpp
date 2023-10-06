// CollisionHandler.cpp
#include "CollisionHandler.h"
#include <algorithm>

void CollisionHandler::handleLaserLanderCollisions(std::vector<Laser> &lasers, std::vector<Lander> &landers, int &score)
{
    for (auto itLaser = lasers.begin(); itLaser != lasers.end();)
    {
        for (auto itLander = landers.begin(); itLander != landers.end();)
        {
            if (!itLander->isDestroyed() && itLaser->shape.getGlobalBounds().intersects(itLander->sprite.getGlobalBounds()))
            {
                score += 10;
                itLander->destroy();
                itLaser = lasers.erase(itLaser);
                break;
            }
            else
            {
                ++itLander;
            }
        }

        if (itLaser != lasers.end())
        {
            ++itLaser;
        }
    }
}

void CollisionHandler::handleLaserHumanoidCollisions(std::vector<Laser> &lasers, std::vector<Humanoid> &humanoids)
{
    for (auto itLaser = lasers.begin(); itLaser != lasers.end();)
    {
        for (auto itHumanoid = humanoids.begin(); itHumanoid != humanoids.end();)
        {
            if (!itHumanoid->isDestroyed() && itHumanoid->checkCollisionWithLaser(*itLaser))
            {
                itHumanoid->destroy();
                itLaser = lasers.erase(itLaser);
                break;
            }
            else
            {
                ++itHumanoid;
            }
        }

        if (itLaser != lasers.end())
        {
            ++itLaser;
        }
    }
}

bool CollisionHandler::handlePlayerLanderCollisions(const Player &player, const std::vector<Lander> &landers)
{
    for (const Lander &lander : landers)
    {
        if (!lander.isDestroyed() && player.getGlobalBounds().intersects(lander.sprite.getGlobalBounds()))
        {
            return true; // Player collided with a lander
        }
    }
    return false;
}

bool CollisionHandler::handlePlayerMissileCollisions(const Player &player, const std::vector<Missile> &missiles)
{
    for (const Missile &missile : missiles)
    {
        if (missile.shape.getGlobalBounds().intersects(player.getGlobalBounds()))
        {
            return true; // Player collided with a missile
        }
    }
    return false;
}
