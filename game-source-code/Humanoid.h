#pragma once
#include "Laser.h"
#include <SFML/Graphics.hpp>

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
    bool isPickedUpByPlayer() const;
    void setPickedUpByPlayer(bool pickedUp);

private:
    bool pickedUpByPlayer;

    bool freeFall = false;
    bool carried;
    bool destroyed;
    sf::Texture humanoidTexture;
};