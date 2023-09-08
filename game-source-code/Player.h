#pragma once

#include <SFML/Graphics.hpp>

class Player
{
public:
    Player(float x, float y, float speed, int width, int height);

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void draw(sf::RenderWindow &window);
    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getPosition() const;
    // Add this method declaration to the Player class
    void resetPosition();

private:
    sf::RectangleShape shape;
    float playerSpeed;
    int windowWidth;
    int windowHeight;
};
