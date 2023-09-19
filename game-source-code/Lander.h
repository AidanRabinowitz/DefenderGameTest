#pragma once

#include <SFML/Graphics.hpp>
#include "GameConstants.h" // Include your game constants here
#include "Humanoid.h"
#include <cmath>
#include <limits>
class Lander
{
public:
    Lander();
    void reset();
    void update();
    void render(sf::RenderWindow &window);
    sf::Vector2f getPosition() const;
    sf::Sprite &getSprite();
    void moveLanderUp();
    Humanoid *attachedHumanoid;

    bool isDestroyed() const;
    sf::Sprite landerSprite;
    sf::Texture landerTexture;
    void destroy();
    Humanoid *findNearestHumanoid(const std::vector<Humanoid> &humanoids) const;
    float getDistance(const sf::Vector2f &targetPosition);
    void moveTowards(const sf::Vector2f &targetPosition);
    void attachToHumanoid(Humanoid *humanoid); // Attach the Lander to a Humanoid
    bool isAttached() const;                   // Check if the Lander is attached to a Humanoid
    Humanoid *getAttachedHumanoid() const;     // Get the attached Humanoid
private:
    float calculateDistance(const sf::Vector2f &point1, const sf::Vector2f &point2) const;
    sf::Vector2f velocity;

    bool destroyed;
};
