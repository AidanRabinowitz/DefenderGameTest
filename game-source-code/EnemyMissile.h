#ifndef ENEMYMISSILE_H
#define ENEMYMISSILE_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class EnemyMissile
{
public:
    // Constructor to initialize the missile
    EnemyMissile(sf::Vector2f startPosition, sf::Vector2f targetDirection);

    // Update method to move the missile
    void update(float deltaTime);

    // Draw method to render the missile
    void draw(sf::RenderWindow &window) const;
    sf::Clock fireTimer;

private:
    sf::RectangleShape missileShape; // The visual representation of the missile
    float velocity;                  // The missile's velocity
    sf::Vector2f targetDirection;    // The direction vector towards the target
};

#endif // ENEMYMISSILE_H
