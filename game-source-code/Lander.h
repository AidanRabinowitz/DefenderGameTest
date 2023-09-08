#ifndef LANDER_H
#define LANDER_H

#include <SFML/Graphics.hpp>

class Lander
{
public:
    Lander();
    void spawn(sf::RenderWindow &window, std::vector<Lander> &landers);
    void move();
    void draw(sf::RenderWindow &window);
    bool &isDestroyed();             // Return a reference to the destroyed flag.
    const bool &isDestroyed() const; // For const objects.
    void destroy();
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    sf::Clock missileTimer;
    bool destroyed;

private:
};

#endif // LANDER_H
