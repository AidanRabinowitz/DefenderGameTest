#pragma once

#include <SFML/Graphics.hpp>
#include "GameConstants.h" // Include your game constants here

class Lander
{
public:
    Lander();

    // You can add more member functions as needed
    void reset();
    void update();
    void render(sf::RenderWindow &window);
    sf::Vector2f getPosition() const;

    // Getter functions
    sf::Sprite &getSprite();
    bool isDestroyed() const;
    sf::Sprite landerSprite;
    sf::Texture landerTexture;
    void destroy();

private:
    bool destroyed;
    // Add any other private members as needed
};
