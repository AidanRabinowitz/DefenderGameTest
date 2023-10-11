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
    /**
     * @brief Construct a new Collision Handler object
     * 
     */
    CollisionHandler() = default;

    /**
     * @brief A function that handles collisions between lasers and landers.
     * i.e. detects and resolves collisions between lasers fired by the player
     * and landers. When a collision occurs, the score is updated,
     * and the lander is destroyed.
     * 
     * @param lasers A reference to the vector of Laser objects representing player-fired lasers.
     * @param landers A reference to the vector of Lander objects representing enemy landers.
     * @param score  An integer reference representing the player's score.
     */
    void handleLaserLanderCollisions(std::vector<Laser> &lasers, std::vector<Lander> &landers, int &score);

    /**
     * @brief A function that handles collisions between lasers and humanoids.
     * i.e. detects and resolves collisions between lasers fired by the player
     * and humanoids. When a collision occurs, the humanoid is destroyed.
     *
     * @param lasers A reference to the vector of Laser objects representing player-fired lasers.
     * @param humanoids A reference to the vector of Humanoid objects representing collectible humanoids. 
     */
    void handleLaserHumanoidCollisions(std::vector<Laser> &lasers, std::vector<Humanoid> &humanoids);

    /**
     * @brief A function that handles collisions between the player and landers.
     * i.e. checks for collisions between the player's spaceship and landers.
     * It returns true if a collision is detected, indicating that the player has collided
     * with a lander.
     * 
     * @param player A constant reference to the Player object representing the player's spaceship.
     * @param landers A constant reference to the vector of Lander objects representing enemy landers.
     * @return true if a collision between the player and landers is detected; otherwise, false.
     */
    bool handlePlayerLanderCollisions(const Player &player, const std::vector<Lander> &landers);

    /**
     * @brief A function that handles collisions between the player and missiles.
     * i.e. checks for collisions between the player's spaceship and lander missiles.
     * It returns true if a collision is detected, indicating that the player has been hit by a missile.
     * 
     * @param player A constant reference to the Player object representing the player's spaceship.
     * @param missiles A constant reference to the vector of Missile objects representing lander missiles.
     * @return true if a collision between the player and missiles is detected; otherwise, false.
     */
    bool handlePlayerMissileCollisions(const Player &player, const std::vector<Missile> &missiles);
};
