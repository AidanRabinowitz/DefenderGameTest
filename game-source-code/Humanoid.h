#pragma once
#include "Laser.h"
#include <SFML/Graphics.hpp>

class Humanoid
{
public:
    Humanoid();

    // Update function to handle movement and collisions
    void update();

    // Render function to draw the humanoid
    void render(sf::RenderWindow &window) const;

    // Getter function to check if the humanoid is touching something
    bool isTouching(const sf::FloatRect &bounds);
    void fall(float deltaTime, float gravity);
    sf::Sprite humanoidSprite;
    bool isDestroyed() const;

    void destroy();
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f &newPosition);
    void moveHumanoid(float speed);
    void moveHumanoidDown();

    sf::Sprite &getSprite();
    bool isAttached() const;
    void setAttached(bool value);
    bool checkCollisionWithLaser(const Laser &laser) const;

private:
    bool attached = false;
    sf::Texture humanoidTexture;
    bool destroyed;
    sf::Vector2f position;
    sf::Vector2f velocity;
    // Add other member variables as needed
};