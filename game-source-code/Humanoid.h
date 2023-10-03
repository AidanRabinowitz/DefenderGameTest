#pragma once
#include "Laser.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>
class Humanoid
{
public:
    Humanoid();
    static int humansKilled; // Declare humans killed as static

    void render(sf::RenderWindow &window) const;
    sf::Sprite humanoidSprite;
    void setPosition(float x, float y);
    bool isCarried() const;
    void setCarried(bool carriedStatus);
    void destroy();
    bool isDestroyed() const;
    // Update method to check position and destroy if out of bounds
    void update(const sf::Vector2f &playerPosition, const Player &player);
    bool checkCollisionWithLaser(const Laser &laser) const;
    void setFreeFall(bool fallStatus);
    sf::Texture humanoidTexture;
    void passengerMovement(float offsetX, float offsetY);
    bool isTouchingPlayer();
    void reset();
    sf::Vector2f originalPosition;
    int humanoidCounter;
    void setOriginalPosition(float x, float y);

private:
    bool touchingPlayer = false;
    bool pickedUpByPlayer;
    bool pickedUpAndDropped;
    bool freeFall = false;
    bool carried;
    bool destroyed;
};