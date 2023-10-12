#pragma once
#include "Player.h"
#include <SFML/Graphics.hpp>

class FuelBar
{
public:
    /**
     * @brief Construct a new Fuel Bar object with parameters.
     * 
     * @param maxWidth The maximum width of the fuel bar.
     * @param height The height of the fuel bar.
     * @param initialFuel The initial fuel capacity of the bar.
     */
    FuelBar(float maxWidth, float height, float initialFuel);

    /**
     * @brief A function to reset the fuel bar to its initial state, restoring the initial fuel capacity.
     * 
     */
    void reset();

    /**
     * @brief A function to set the current fuel level and update the visual representation of the bar.
     * 
     * @param currentFuel The current fuel level to set.
     */
    void setFuel(float currentFuel);

    /**
     * @brief A function to get the maximum width of the fuel bar.
     * 
     * @return float; the maximum width of the fuel bar.
     */
    float getMaxWidth() const;

    /**
     * @brief A function to render the fuel bar to the given SFML window.
     * 
     * @param window A reference to the SFML RenderWindow where the fuel bar should be rendered.
     */
    void render(sf::RenderWindow &window) const;
    /**
     * @brief A function to get the current fuel level of the bar.
     * 
     * @return float; the current fuel level.
     */
    float getCurrentFuel() const;

private:
    sf::RectangleShape bar; // The visual representation of the fuel bar
    float maxWidth;         // The maximum width of the fuel bar
    float initialFuel;      // The initial total fuel capacity
    float currentFuel;      // The current fuel level
    void updateBarSize();
};