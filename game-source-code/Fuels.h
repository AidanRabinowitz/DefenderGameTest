#ifndef FUELS_H
#define FUELS_H

#include <SFML/Graphics.hpp>
#include "GameConstants.h" // Include any relevant constants
#include "Player.h"
class Fuels
{
public:
    Fuels();
    void update();
    void render(sf::RenderWindow &window) const;
    bool checkCollisionWithPlayer(const Player &player);
    bool isDestroyed() const;
    void destroy();
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f &newPosition);
    sf::Texture fuelsTexture;
    sf::Sprite fuelsSprite;
    void spawnFuel(std::vector<Fuels> &fuels, const sf::Texture &fuelsTexture);

private:
    sf::Vector2f position;
    bool destroyed;
    bool checkCollision(const sf::FloatRect &playerBounds);
};

#endif // FUELS_H
