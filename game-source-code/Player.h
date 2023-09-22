#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Humanoid.h"
class Player : public sf::Sprite
{
public:
    Player();
    void setPosition(float x, float y);
    void move(float offsetX, float offsetY);
    void setTexture(const sf::Texture &texture);
    void setScale(const sf::Vector2f &factors);
    void render(sf::RenderWindow &window) const;
    const sf::Vector2f &getPosition() const;
    const sf::FloatRect getGlobalBounds() const;
    bool isTouchingHumanoid(const Humanoid &humanoid) const;
    void renderFuelBar(sf::RenderWindow &window) const; // Add this function to render the fuel bar
    void consumeFuel(float deltaTime);
    float getCurrentFuel() const;
    float getTotalFuel() const;
    bool hasFuel() const; // Add this function to check if there is fuel
    bool descending;      // Flag to indicate whether the player is descending
    void resetCurrentFuel();

private:
    sf::Texture playerTexture;
    float totalFuel;
    float currentFuel;
    float fuelConsumptionRate; // Fuel consumption rate per second
    sf::Sprite playerSprite;
};

#endif // PLAYER_H
