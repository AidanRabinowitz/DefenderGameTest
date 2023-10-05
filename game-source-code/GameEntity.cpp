#include "GameEntity.h"

GameEntity::GameEntity()
{
    // Common initialization for all game entities if needed
}

GameEntity::GameEntity(sf::Vector2f initialPosition, sf::Vector2f targetPosition)
{
    // Initialize position and other properties as needed
    sprite.setPosition(initialPosition);
    // ...
    // Perform SFML-related operations here, e.g., creating shapes or sprites
}

GameEntity::~GameEntity()
{
    // Common cleanup for all game entities if needed
}

void GameEntity::move(float xOffset, float yOffset)
{
    sprite.move(xOffset, yOffset);
}

sf::Vector2f GameEntity::getPosition() const
{
    return sprite.getPosition();
}

void GameEntity::draw(sf::RenderWindow &window)
{
    window.draw(shape);
}

void GameEntity::render(sf::RenderWindow &window) const
{
    // Draw the humanoid sprite
    window.draw(sprite);
}
