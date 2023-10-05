#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <SFML/Graphics.hpp>

class GameEntity
{
public:
    GameEntity();

    GameEntity(sf::Vector2f initialPosition, sf::Vector2f targetPosition);

    virtual ~GameEntity();

    // Common SFML functions and variables
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f position;
    sf::Vector2f velocity;

    // Common methods
    void move(float xOffset, float yOffset);
    void draw(sf::RenderWindow &window);
    void render(sf::RenderWindow &window) const;

    sf::Vector2f getPosition() const;
    // Laser methods
    sf::RectangleShape shape; // Rectangle shape for rendering

    sf::Vector2f target; // Missile target
    sf::Vector2f originalPosition;
    sf::Vector2f finalPosition;
};

#endif // GAMEENTITY_H
