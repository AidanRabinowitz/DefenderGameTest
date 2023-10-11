#pragma once
#include "Humanoid.h"
#include "GameConstants.h" // Include your game constants here
#include <cmath>
#include <limits>
#include <memory>

class Lander : public GameEntity
{
public:

    /**
     * @brief Construct a new Lander object
     * 
     * @param id The identifier for the lander.
     * @param humanoids Reference to a vector of humanoid objects.
     */
    Lander(int id, std::vector<Humanoid> &humanoids);

    /**
     * @brief A function to move the lander and check if it's out of bounds.
     * 
     */
    void moveAndCheckBounds();

    /**
     * @brief A function to set the identifier for the lander.
     * 
     * @param id The identifier to set.
     */
    void setId(int id);

    /**
     * @brief A function to reset the state of the lander. 
     * 
     */
    void reset();

    /**
     * @brief A function to update the lander's behavior and interactions.
     * 
     */
    void update();

    /**
     * @brief A function to render the lander on a window.
     * 
     * @param window The SFML RenderWindow.
     */
    void render(sf::RenderWindow &window);

    /**
     * @brief A function to check if the lander is destroyed.
     * 
     * @return true if destroyed, false otherwise.
     */
    bool isDestroyed() const;

    /**
     * @brief  A function to destroy the lander.
     * 
     */
    void destroy();

    /**
     * @brief A function to check if the lander is carrying a humanoid.
     * 
     * @return true  if carrying a humanoid, false otherwise.
     */
    bool isCarryingHumanoid() const;

    /**
     * @brief A function to check if the lander is moving up.
     * 
     * @return true if moving up, false otherwise.
     */
    bool isMovingUp() const;

private:
    Humanoid *carriedHumanoid;// Pointer to the carried humanoid.
    sf::Clock spawnTimer;
    std::vector<Humanoid> &humanoids; // Reference to the humanoids container
    bool destroyedByLaser;
    bool carryingHumanoid;
    bool onWayToTop;
    bool destroyed;
    int id;
};