#ifndef MISSILE_H
#define MISSILE_H

#include <SFML/Graphics.hpp>

class Missile
{
public:
    Missile(const sf::Vector2f &position, const sf::Vector2f &target);
    void move();
    void draw(sf::RenderWindow &window);
    sf::RectangleShape shape;
    sf::Vector2f velocity;

private:
};

#endif // MISSILE_H
