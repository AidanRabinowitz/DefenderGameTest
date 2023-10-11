#ifndef FUELS_H
#define FUELS_H

#include <SFML/Graphics.hpp>
#include "GameConstants.h" // Include any relevant constants
#include "Player.h"
#include "GameEntity.h"

class Fuels : public GameEntity
{
public:
    /**
     * @brief Construct a new Fuels object
     * 
     */
    Fuels();

    /**
     * @brief A function to update the fuel canister's position.
     * 
     */
    void update();

    /**
     * @brief A function to render the fuel canister in the provided SFML window.
     * 
     * @param window A reference to the SFML RenderWindow where the fuel canister should be rendered.
     */
    void render(sf::RenderWindow &window) const;

    /**
     * @brief A function to check for collisions with the player.
     * 
     * @param player The Player object to check for collision with.
     * @return true if a collision is detected, false otherwise.
     */
    bool checkCollisionWithPlayer(const Player &player);

    /**
     * @brief A function to check if the fuel canister has been destroyed.
     * 
     * @return true if the fuel canister is destroyed, false otherwise.
     */
    bool isDestroyed() const;

    /**
     * @brief A function to mark the fuel canister as destroyed.
     * 
     */
    void destroy();

    /**
     * @brief A function to set the Position of the fuel canister.
     * 
     * @param newPosition The new position to set.
     */
    void setPosition(const sf::Vector2f &newPosition);

    /**
     * @brief A function to spawn a new fuel canister and add it to the provided vector of fuels.
     * 
     * @param fuels A reference to the vector of fuel canisters.
     * @param fuelsTexture The texture for the fuel canister.
     */
    void spawnFuel(std::vector<Fuels> &fuels, const sf::Texture &fuelsTexture);

private:
    sf::Vector2f position; // The position of the fuel canister
    bool destroyed; // Indicates whether the fuel canister is destroyed

    /**
     * @brief A function to check for collisions with a bounding box (e.g., player bounds).
     * 
     * @param playerBounds The bounding box to check for collisions with.
     * @return true if a collision is detected, false otherwise.
     */
    bool checkCollision(const sf::FloatRect &playerBounds);
};

#endif // FUELS_H
