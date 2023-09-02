#ifndef ENEMYLANDER_H
#define ENEMYLANDER_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>

class EnemyLander
{
public:
    EnemyLander(sf::Vector2f position, float fireRate, std::vector<sf::RectangleShape> &missiles);
    void update(float deltaTime, sf::Vector2f playerShipPosition, std::vector<sf::RectangleShape> &enemyMissiles);
    void draw(sf::RenderWindow &window) const;

private:
    sf::Clock fireTimer;
    sf::RectangleShape landerShape;
    float minDistance;
    float fireRate;
    bool movingUp;
    std::vector<sf::RectangleShape> &enemyMissiles; // Reference to the missiles vector
    void missileFire();
};

#endif // ENEMYLANDER_H
