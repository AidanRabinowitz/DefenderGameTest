#pragma once
// EnemyLander.h
#ifndef ENEMYLANDER_H
#define ENEMYLANDER_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "EnemyMissile.h"

class EnemyLander
{
public:
    EnemyLander(sf::Vector2f position);

    void update(float deltaTime, sf::Vector2f playerShipPosition, std::vector<EnemyMissile> &missiles);
    void draw(sf::RenderWindow &window) const;

private:
    sf::RectangleShape landerShape;
    sf::Vector2f velocity; // Add velocity for automatic movement
    float minDistance;     // Minimum distance to maintain from player
    float fireCooldown;    // Cooldown for missile firing
    float fireTimer;       // Timer to track cooldown
    bool movingUp;         // Add this line to declare the movingUp variable
    void missileFire(const sf::Vector2f &targetPosition, std::vector<EnemyMissile> &missiles);
};
#endif // ENEMYLANDER_H
