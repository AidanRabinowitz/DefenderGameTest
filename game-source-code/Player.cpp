#include "Player.h"

Player::Player(float x, float y, float speed, int width, int height)
    : playerSpeed(speed), windowWidth(width), windowHeight(height)
{
    shape.setSize(sf::Vector2f(50, 50));
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(x, y);
}

void Player::moveLeft()
{
    if (shape.getPosition().x > 0)
    {
        shape.move(-playerSpeed, 0);
    }
}

void Player::moveRight()
{
    if (shape.getPosition().x < windowWidth - 50)
    {
        shape.move(playerSpeed, 0);
    }
}

void Player::moveUp()
{
    if (shape.getPosition().y > 0)
    {
        shape.move(0, -playerSpeed);
    }
}

void Player::moveDown()
{
    if (shape.getPosition().y < windowHeight - 50)
    {
        shape.move(0, playerSpeed);
    }
}

void Player::draw(sf::RenderWindow &window)
{
    window.draw(shape);
}

sf::FloatRect Player::getGlobalBounds() const
{
    return shape.getGlobalBounds();
}

sf::Vector2f Player::getPosition() const
{
    return shape.getPosition();
}

void Player::resetPosition()
{
    shape.setPosition(windowWidth / 2 - 25, windowHeight - 60);
}
