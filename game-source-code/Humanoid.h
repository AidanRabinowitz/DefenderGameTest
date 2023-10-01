#pragma once
#include "Laser.h"
#include <SFML/Graphics.hpp>
#include <iostream>
class Humanoid
{
public:
    Humanoid();
    void render(sf::RenderWindow &window) const;
    sf::Sprite humanoidSprite;
    void setPosition(float x, float y);
    int humansKilled;
    bool isCarried() const;
    void setCarried(bool carriedStatus);
    void destroy();
    bool isDestroyed() const;
    // Update method to check position and destroy if out of bounds
    void update();
    bool checkCollisionWithLaser(const Laser &laser) const;
    void setFreeFall(bool fallStatus);

private:
    bool pickedUpByPlayer;
    bool pickedUpAndDropped;
    bool freeFall = false;
    bool carried;
    bool destroyed;
    sf::Texture humanoidTexture;
};