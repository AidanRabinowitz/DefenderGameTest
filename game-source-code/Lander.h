#pragma once

#include <SFML/Graphics.hpp>
#include "GameConstants.h" // Include your game constants here
#include <cmath>
#include <limits>
#include <memory>
class Lander
{
public:
    Lander();
    void moveAndCheckBounds();

    void reset();
    void update();
    void render(sf::RenderWindow &window);
    sf::Vector2f getPosition() const;
    sf::Sprite &getSprite();

    bool isDestroyed() const;
    sf::Sprite landerSprite;
    sf::Texture landerTexture;
    void destroy();

private:
    sf::Vector2f velocity;

    bool destroyed;
};
