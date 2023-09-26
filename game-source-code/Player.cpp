#include "Player.h"

Player::Player()
{
    // Initialize the player's properties as needed
}

void Player::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

void Player::move(float offsetX, float offsetY)
{
    sprite.move(offsetX, offsetY);
}

void Player::setTexture(const sf::Texture &texture)
{
    sprite.setTexture(texture);
}

void Player::setScale(const sf::Vector2f &factors)
{
    sprite.setScale(factors);
}

void Player::render(sf::RenderWindow &window) const
{
    window.draw(sprite);
}

const sf::Vector2f &Player::getPosition() const
{
    return sprite.getPosition();
}

const sf::FloatRect Player::getGlobalBounds() const
{
    return sprite.getGlobalBounds();
}