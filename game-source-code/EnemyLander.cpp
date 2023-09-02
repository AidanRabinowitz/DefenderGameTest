#include "EnemyLander.h"

EnemyLander::EnemyLander(sf::Vector2f position, float fireRate, std::vector<sf::RectangleShape> &missiles)
    : minDistance(100.f), fireRate(fireRate), fireTimer(), movingUp(true), enemyMissiles(missiles)
{
    landerShape.setSize(sf::Vector2f(30.f, 30.f));
    landerShape.setFillColor(sf::Color::Red);
    landerShape.setPosition(position);
}

void EnemyLander::update(float deltaTime, sf::Vector2f playerShipPosition, std::vector<sf::RectangleShape> &enemyMissiles)
{
    if (fireTimer.getElapsedTime().asSeconds() >= fireRate)
    {
        missileFire();
        fireTimer.restart();
    }

    float horizontalSpeed = 100.f;

    if (movingUp && landerShape.getPosition().y <= minDistance)
    {
        movingUp = false;
    }
    else if (!movingUp && landerShape.getPosition().y >= 600.f)
    {
        movingUp = true;
    }

    if (movingUp)
    {
        landerShape.move(sf::Vector2f(0.f, -horizontalSpeed * deltaTime));
    }
    else
    {
        landerShape.move(sf::Vector2f(0.f, horizontalSpeed * deltaTime));
    }
}

void EnemyLander::draw(sf::RenderWindow &window) const
{
    window.draw(landerShape);
}

void EnemyLander::missileFire()
{
    // Create a missile instance starting from the lander's position
    sf::RectangleShape missile(sf::Vector2f(10.f, 10.f));
    missile.setFillColor(sf::Color::Blue);
    missile.setPosition(landerShape.getPosition());

    enemyMissiles.push_back(missile);
}
