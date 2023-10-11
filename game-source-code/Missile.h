#ifndef MISSILE_H
#define MISSILE_H
#include "Lander.h"
#include "GameEntity.h"
#include <SFML/Graphics.hpp>

class Missile : public GameEntity
{
public:

    /**
     * @brief Construct a new Missile object
     * 
     * @param initialPosition The initial position of the missile.
     * @param targetPosition The position of the missile's target.
     */
    Missile(sf::Vector2f initialPosition, sf::Vector2f targetPosition);

    /**
     * @brief A function to move the missile towards its target.
     * 
     */
    void move();

    /**
     * @brief A function to draw the missile on the game window.
     * 
     * @param window The SFML RenderWindow on which to draw the missile.
     */
    void draw(sf::RenderWindow &window);

private:
    sf::Vector2f target; // Add the target member variable
};

#endif // MISSILE_H
