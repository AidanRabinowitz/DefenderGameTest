#include "PlayerLaser.h"

PlayerLaser::PlayerLaser(const sf::Vector2f &position)
    : speed(800.f)
{
    shape.setSize(sf::Vector2f(5.f, 15.f)); // Adjust size
    shape.setFillColor(sf::Color::Cyan);
    shape.setPosition(position);
}

void PlayerLaser::update(float deltaTime)
{
    shape.move(speed * deltaTime, 0.f);
}

void PlayerLaser::draw(sf::RenderWindow &window) const
{
    window.draw(shape);
}

bool PlayerLaser::isOutOfBounds()
{
    return shape.getPosition().y + shape.getSize().y < 0.f;
}
void PlayerLaser::move(float xOffset, float yOffset)
{
    // Move the laserShape
}
sf::Vector2f PlayerLaser::getPosition() const
{
    return shape.getPosition();
}