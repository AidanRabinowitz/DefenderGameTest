#include "FuelBar.h"

FuelBar::FuelBar(float width, float height, float totalFuel = 100.f)
    : maxWidth(width)
{
    bar.setSize(sf::Vector2f(maxWidth, height));
    bar.setFillColor(sf::Color::Green);
    initialTotalFuel = totalFuel;
}

void FuelBar::resetFuelBar()
{
    currentFuel = initialTotalFuel;
    setFuel(currentFuel, initialTotalFuel); // Update the fuel bar's width
}

void FuelBar::setFuel(float currentFuel, float totalFuel)
{
    float fuelPercentage = currentFuel / totalFuel;
    bar.setSize(sf::Vector2f(maxWidth * fuelPercentage, bar.getSize().y));
}

// void FuelBar::update()
// {
//     // You can add update logic here if needed
// }

void FuelBar::render(sf::RenderWindow &window) const
{
    window.draw(bar);
}
