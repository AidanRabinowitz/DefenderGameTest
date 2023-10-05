#ifndef LASER_H
#define LASER_H

#include "GameConstants.h"
#include <SFML/Graphics.hpp>
#include "GameEntity.h"

class Laser : public GameEntity
{
public:
    Laser();
    void fire(sf::Vector2f startPosition, sf::Vector2f mousePosition);
    void move();
    bool isFired() const;
    void setFired(bool fired);
    bool fired;

private:
};

#endif // LASER_H
