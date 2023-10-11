#pragma once
#include "Laser.h"
#include "Player.h"
#include "GameEntity.h"
#include <SFML/Graphics.hpp>
#include <iostream>
class Humanoid : public GameEntity
{
public:

    /**
     * @brief Construct a new Humanoid object.
     * 
     */
    Humanoid();

    /**
     * @brief Declare humans killed as static
     * 
     */
    static int humansKilled; 

    /**
     * @brief A function to remove destroyed humanoids from the provided vector.
     * 
     * @param humanoids The vector of humanoid objects to clean.
     */
    void removeDestroyed(std::vector<Humanoid> &humanoids);

    /**
     * @brief A function to set the Position of the humanoid.
     * 
     * @param x The x-coordinate of humanoid.
     * @param y The y-coordinate of humanoid.
     */
    void setPosition(float x, float y);

    /**
     * @brief A function to check if the humanoid is being carried by the player.
     * 
     * @return true if the humanoid is carried, false otherwise.
     */
    bool isCarried() const;

    /**
     * @brief A function to set whether the humanoid is being carried by the player.
     * 
     * @param carriedStatus The status of being carried.
     */
    void setCarried(bool carriedStatus);

    /**
     * @brief A function to destroy the humanoid (i.e. when killed by a player).
     * 
     */
    void destroy();

    /**
     * @brief A function to check if the humanoid is destroyed.
     * 
     * @return true if destroyed, false otherwise.
     */
    bool isDestroyed() const;

    // Update method to check position and destroy if out of bounds
    /**
     * @brief A function to update the humanoid's behavior and position.
     * 
     * @param playerPosition The position of the player.
     * @param player The player object.
     * @param window The game window.
     */
    void update(const sf::Vector2f &playerPosition, const Player &player, const sf::RenderWindow &window);

    /**
     * @brief A function to check if the humanoid collides with a laser.
     * 
     * @param laser The laser to check for collision.
     * @return true if a collision occurs, false otherwise.
     */
    bool checkCollisionWithLaser(const Laser &laser) const;

    /**
     * @brief A function to set  whether the humanoid is in free fall.
     * 
     * @param fallStatus The status of being in free fall.
     */
    void setFreeFall(bool fallStatus);

    /**
     * @brief  A function to perform passenger movement when carried by the player.
     * 
     * @param offsetX The horizontal offset.
     * @param offsetY The vertical offset.
     */
    void passengerMovement(float offsetX, float offsetY);

    /**
     * @brief  A function to check if the humanoid is currently touching the player.
     * 
     * @return true if touching the player, false otherwise.
     */
    bool isTouchingPlayer();

    /**
     * @brief A function to reset the humanoid's state and position to the original state.
     * 
     */
    void reset();

    /**
     * @brief A function to set the original position of the humanoid.
     * 
     * @param x The original x-coordinate of humanoid.
     * @param y The original y-coordinate of humanoid.
     */
    void setOriginalPosition(float x, float y);
    /**
     * @brief A function to check if the humanoid is in free fall.
     * 
     * @return true if in free fall, false otherwise.
     */
    bool isFreeFall() const;

private:
    bool touchingPlayer = false;
    bool pickedUpByPlayer;
    bool pickedUpAndDropped;
    bool freeFall = false;
    bool carried;
    bool destroyed;
};