#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
class Player : public sf::Sprite
{
public:

    /**
     * @brief Construct a new Player object
     * 
     */
    Player();

    /**
     * @brief A function to set the Position of the player.
     * 
     * @param x The x-coordinate of the new position of the player.
     * @param y The y-coordinate of the new position of the player.
     */
    void setPosition(float x, float y);

    /**
     * @brief A function to move the player by a specified offset.
     * 
     * @param offsetX The horizontal offset.
     * @param offsetY The vertical offset.
     */
    void move(float offsetX, float offsetY);

    /**
     * @brief A function to set the texture of the player.
     * 
     * @param texture The new texture for the player.
     */
    void setTexture(const sf::Texture &texture);

    /**
     * @brief A function to set the scale of the player.
     * 
     * @param factors The scaling factors in x and y directions.
     */
    void setScale(const sf::Vector2f &factors);

    /**
     * @brief A function to render the player on the game window.
     * 
     * @param window The SFML RenderWindow on which to render the player.
     */
    void render(sf::RenderWindow &window) const;

    /**
     * @brief A function to get the current position of the player.
     * 
     * @return const sf::Vector2f& ; The current position of the player.
     */
    const sf::Vector2f &getPosition() const;

    /**
     * @brief A function to get the global bounding rectangle of the player.
     * 
     * @return const sf::FloatRect; The global bounding rectangle of the player.
     */
    const sf::FloatRect getGlobalBounds() const;

    /**
     * @brief A function to render the player's fuel bar on the game window.
     * 
     * @param window The SFML RenderWindow on which to render the fuel bar.
     */
    void renderFuelBar(sf::RenderWindow &window) const; 

    /**
     * @brief A function to consume fuel based on player's movements.
     * 
     * @param deltaTime The time elapsed since the last frame.
     */
    void consumeFuel(float deltaTime);

    /**
     * @brief A function to get the current fuel level of the player.
     * 
     * @return float; The current fuel level.
     */
    float getCurrentFuel() const;

    /**
     * @brief A function get the total fuel capacity of the player.
     * 
     * @return float; The total fuel capacity.
     */
    float getTotalFuel() const;

    /**
     * @brief A function to check if the player has any remaining fuel.
     * 
     * @return true if the player has remaining fuel, false otherwise.
     */
    bool hasFuel() const; 

    /**
     * @brief A function to reset the current fuel level to its maximum value.
     * 
     */
    void resetCurrentFuel();

    /**
     * @brief A function to handle player movement based on user input.
     * 
     * @param window The SFML RenderWindow for handling input.
     */
    void handleMovement(sf::RenderWindow &window);

private:
    bool descending;           // Flag to indicate whether the player is descending
    float fuelConsumptionRate; // Fuel consumption rate per second
    sf::Texture playerTexture;
    float totalFuel;
    float currentFuel;
    sf::Sprite playerSprite;
};

#endif // PLAYER_H
