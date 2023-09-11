#ifndef LANDER_H
#define LANDER_H
#include "Missile.h"
#include <SFML/Graphics.hpp>

class Lander
{
public:
    Lander(const sf::Vector2f &playerPos);
    void spawn(sf::RenderWindow &window, std::vector<Lander> &landers);
    void move();
    void draw(sf::RenderWindow &window);
    bool &isDestroyed();             // Return a reference to the destroyed flag.
    const bool &isDestroyed() const; // For const objects.
    void destroy();
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    sf::Clock missileFireTimer; // Timer for missile firing
    bool destroyed;
    sf::Vector2f getSpawnPosition() const; // Getter for spawn position
    sf::Clock fireRateClock;               // Add this member variable
    sf::Vector2f playerPosition;
    sf::Vector2f getPosition() const;

private:
    sf::Vector2f spawnPosition; // Store the spawn position for each lander
};

#endif // LANDER_H
