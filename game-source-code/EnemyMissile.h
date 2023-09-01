#ifndef ENEMYMISSILE_H
#define ENEMYMISSILE_H

#include <SFML/Graphics.hpp>

class EnemyMissile
{
public:
    // Constructor
    EnemyMissile(sf::Vector2f initialPosition, sf::Vector2f initialVelocity);

    // Destructor
    ~EnemyMissile();

    // Update function to move and update the missile
    void update(float deltaTime);

    // Function to check if the missile is alive
    bool isAlive() const;

    // Function to get the position of the missile
    sf::Vector2f getPosition() const;

    // Function to draw the missile
    void draw(sf::RenderWindow &window);

private:
    sf::CircleShape missileShape;
    sf::Vector2f velocity;
    bool alive;
};

#endif // ENEMYMISSILE_H
