#ifndef FUELS_H
#define FUELS_H

#include <SFML/Graphics.hpp>
#include "GameConstants.h" // Include any relevant constants
#include "Player.h"
#include "GameEntity.h"

class Fuels : public GameEntity
{
public:
    Fuels();
    void update();
    void render(sf::RenderWindow &window) const;
    bool checkCollisionWithPlayer(const Player &player);
    bool isDestroyed() const;
    void destroy();
    void setPosition(const sf::Vector2f &newPosition);
    void spawnFuel(std::vector<Fuels> &fuels, const sf::Texture &fuelsTexture);

private:
    sf::Vector2f position;
    bool destroyed;
    bool checkCollision(const sf::FloatRect &playerBounds);
};

#endif // FUELS_H
