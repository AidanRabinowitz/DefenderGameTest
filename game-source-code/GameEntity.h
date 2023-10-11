#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <SFML/Graphics.hpp>

class GameEntity
{
public:

    /**
     * @brief Construct a new Game Entity object
     * 
     */
    GameEntity();

    /**
     * @brief Construct a new Game Entity object with initial position and target position.
     * 
     * @param initialPosition The initial position of the entity.
     * @param targetPosition The target position of the entity.
     */
    GameEntity(sf::Vector2f initialPosition, sf::Vector2f targetPosition);

    /**
     * @brief A function to destroy the Game Entity object
     * 
     */
    virtual ~GameEntity();

    // Common SFML functions and variables
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f position;
    sf::Vector2f velocity;
    const sf::FloatRect getGlobalBounds() const;

    // Common methods
    /**
     * @brief A function to move the entity by the specified offset.
     * 
     * @param xOffset The horizontal offset to move.
     * @param yOffset The vertical offset to move.
     */
    void move(float xOffset, float yOffset);

    /**
     * @brief  A function to draw the entity on the SFML window.
     * 
     * @param window  A reference to the SFML RenderWindow.
     */
    void draw(sf::RenderWindow &window);

    /**
     * @brief A function to render the entity on the SFML window.
     * 
     * @param window A reference to the SFML RenderWindow.
     */
    void render(sf::RenderWindow &window) const;

    /**
     * @brief A function to get the current position of the entity.
     * 
     * @return sf::Vector2f The position of the entity.
     */
    virtual sf::Vector2f getPosition() const;

    // Laser methods
    sf::RectangleShape shape; // Rectangle shape for rendering
    sf::Vector2f target; // Missile target
    sf::Vector2f originalPosition;
    sf::Vector2f finalPosition;
};

#endif // GAMEENTITY_H
