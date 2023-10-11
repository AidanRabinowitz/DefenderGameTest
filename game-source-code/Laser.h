#ifndef LASER_H
#define LASER_H

#include "GameConstants.h"
#include <SFML/Graphics.hpp>
#include "GameEntity.h"

class Laser : public GameEntity
{
public:

    /**
     * @brief Construct a new Laser object.
     * 
     */
    Laser();

    /**
     * @brief A function to fire the laser from a specified position towards a target mouse position.
     * 
     * @param startPosition The starting position of the laser (usually player's position).
     * @param mousePosition The target position (where the mouse is pointing).
     */
    void fire(sf::Vector2f startPosition, sf::Vector2f mousePosition);

    /**
     * @brief  A function to move the laser.
     * 
     */
    void move();

    /**
     * @brief A function to check if the laser is currently being fired.
     * 
     * @return true if the laser is currently being fired, false otherwise.
     */
    bool isFired() const;

    /**
     * @brief A function to set the Fired status of the laser.
     * i.e. allows you to control whether the laser is actively firing or not.
     * 
     * @param fired True if the laser should be fired, false to stop firing.
     */
    void setFired(bool fired);

    /**
     * @brief Indicates whether the laser is currently fired or not.
     * i.e. This flag is true when the laser is in the fired state, and false otherwise.
     * 
     */
    bool fired;

    /**
     * @brief A function to get the current position of the laser.
     * 
     * @return sf::Vector2f  ; The position of the laser as an sf::Vector2f.
     */
    sf::Vector2f getPosition() const override;

private:
};

#endif // LASER_H
