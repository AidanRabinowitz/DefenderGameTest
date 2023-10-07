#pragma once
#include "Laser.h"
#include "Player.h"
#include "GameEntity.h"
#include <SFML/Graphics.hpp>
#include <iostream>
class Humanoid : public GameEntity
{
public:
    Humanoid();
    static int humansKilled; // Declare humans killed as static
    void removeDestroyed(std::vector<Humanoid> &humanoids);
    void setPosition(float x, float y);
    bool isCarried() const;
    void setCarried(bool carriedStatus);
    void destroy();
    bool isDestroyed() const;
    // Update method to check position and destroy if out of bounds
    void update(const sf::Vector2f &playerPosition, const Player &player, const sf::RenderWindow &window);
    bool checkCollisionWithLaser(const Laser &laser) const;
    void setFreeFall(bool fallStatus);
    void passengerMovement(float offsetX, float offsetY);
    bool isTouchingPlayer();
    void reset();
    int humanoidCounter;
    void setOriginalPosition(float x, float y);
    bool isFreeFall() const;

private:
    bool touchingPlayer = false;
    bool pickedUpByPlayer;
    bool pickedUpAndDropped;
    bool freeFall = false;
    bool carried;
    bool destroyed;
};