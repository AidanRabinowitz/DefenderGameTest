#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class PlayerLaser
{
public:
    PlayerLaser(const sf::Vector2f &position);

    void update(float deltaTime);
    void draw(sf::RenderWindow &window) const;
    bool isOutOfBounds();
    void move(float xOffset, float yOffset);
    sf::Vector2f getPosition() const;

private:
    sf::RectangleShape shape;
    float speed;
};
