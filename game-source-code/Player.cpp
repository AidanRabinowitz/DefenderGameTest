#include "Player.h"

Player::Player(float x, float y, float speed, int width, int height)
    : playerSpeed(speed), windowWidth(width), windowHeight(height)
{
    // shape.setSize(sf::Vector2f(50, 50));
    // shape.setFillColor(sf::Color::Green);
    // shape.setPosition(x, y);
    texture.loadFromFile("resources/landerShip.png");
    playerSprite.setTexture(texture);
    playerSprite.scale(sf::Vector2f(0.1, 0.1));
}

void Player::moveLeft()
{
    if (playerSprite.getPosition().x > 0)
    {
        playerSprite.move(-playerSpeed, 0);
    }
}

void Player::moveRight()
{
    if (playerSprite.getPosition().x < windowWidth - 50)
    {
        playerSprite.move(playerSpeed, 0);
    }
}

void Player::moveUp()
{
    if (playerSprite.getPosition().y > 0)
    {
        playerSprite.move(0, -playerSpeed);
    }
}

void Player::moveDown()
{
    if (playerSprite.getPosition().y < windowHeight - 50)
    {
        playerSprite.move(0, playerSpeed);
    }
}

void Player::draw(sf::RenderWindow &window)
{
    window.draw(playerSprite);
}

sf::FloatRect Player::getGlobalBounds() const
{
    return playerSprite.getGlobalBounds();
}

sf::Vector2f Player::getPosition() const
{
    return playerSprite.getPosition();
}

void Player::resetPosition()
{
    playerSprite.setPosition(windowWidth / 2 - 25, windowHeight - 60);
}
