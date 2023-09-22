#pragma once

#include <SFML/Graphics.hpp>

class FuelBar
{
public:
    FuelBar(float width, float height, float initialTotalFuel);
    float initialTotalFuel;
    void resetFuelBar();

    void setFuel(float currentFuel, float totalFuel);
    void render(sf::RenderWindow &window) const;
    float currentFuel;

private:
    sf::RectangleShape bar;
    float maxWidth;
};
