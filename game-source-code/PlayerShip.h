#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "PlayerLaser.h"

class PlayerShip
{
public:
    PlayerShip(sf::Vector2f position);
    void update(float deltaTime);
    void draw(sf::RenderWindow &window);
    void handleMouseClick(const sf::Event &event, std::vector<PlayerLaser> &lasers);
    void fireLaser(std::vector<PlayerLaser> &lasers);
    sf::Vector2f getPosition() const; // Added getPosition member function

private:
    sf::RectangleShape ship;
    sf::Vector2f shipSize;
    float speed;
    std::vector<PlayerLaser> lasers; // Use forward declaration of PlayerLaser
};

#endif // PLAYERSHIP_H
