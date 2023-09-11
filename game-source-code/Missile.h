#ifndef MISSILE_H
#define MISSILE_H
#include "Lander.h"
#include <SFML/Graphics.hpp>

class Missile
{
public:
    Missile(sf::Vector2f initialPosition, sf::Vector2f targetPosition);
    void move();
    void draw(sf::RenderWindow &window);
    sf::RectangleShape shape;
    sf::Vector2f velocity;

private:
    sf::Vector2f target; // Add the target member variable
};

#endif // MISSILE_H
