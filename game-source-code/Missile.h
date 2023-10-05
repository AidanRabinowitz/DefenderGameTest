#ifndef MISSILE_H
#define MISSILE_H
#include "Lander.h"
#include "GameEntity.h"
#include <SFML/Graphics.hpp>

class Missile : public GameEntity
{
public:
    Missile(sf::Vector2f initialPosition, sf::Vector2f targetPosition);
    void move();
    void draw(sf::RenderWindow &window);

private:
    sf::Vector2f target; // Add the target member variable
};

#endif // MISSILE_H
