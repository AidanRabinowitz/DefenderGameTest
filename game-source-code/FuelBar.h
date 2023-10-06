#pragma once
#include "Player.h"
#include <SFML/Graphics.hpp>

class FuelBar
{
public:
    // Constructor with explicit parameters
    FuelBar(float maxWidth, float height, float initialFuel);

    // Reset the fuel bar to its initial state
    void reset();

    // Set the current fuel level and update the bar
    void setFuel(float currentFuel);

    // Get the maximum width of the fuel bar
    float getMaxWidth() const;

    // Render the fuel bar to the given window
    void render(sf::RenderWindow &window) const;
    float getCurrentFuel() const;

private:
    sf::RectangleShape bar; // The visual representation of the fuel bar
    float maxWidth;         // The maximum width of the fuel bar
    float initialFuel;      // The initial total fuel capacity
    float currentFuel;      // The current fuel level

    // Update the size of the fuel bar based on the current fuel level
    void updateBarSize();
};