#include "FuelBar.h"

FuelBar::FuelBar(float maxWidth, float height, float initialFuel)
    : maxWidth(maxWidth), initialFuel(initialFuel), currentFuel(initialFuel)
{
    // Configure the visual representation of the fuel bar
    bar.setSize(sf::Vector2f(maxWidth, height));
    bar.setFillColor(sf::Color::Green);

    // Initialize the bar size based on the current fuel level
    updateBarSize();
}

void FuelBar::reset()
{
    // Reset the current fuel level to its initial value
    currentFuel = initialFuel;

    // Update the size of the fuel bar
    updateBarSize();
}
float FuelBar::getCurrentFuel() const
{
    return currentFuel;
}

void FuelBar::setFuel(float currentFuel)
{
    // Ensure that the current fuel level does not exceed the initial capacity
    this->currentFuel = std::min(currentFuel, initialFuel);

    // Update the size of the fuel bar
    updateBarSize();
}

float FuelBar::getMaxWidth() const
{
    return maxWidth;
}

void FuelBar::render(sf::RenderWindow &window) const
{
    // Render the fuel bar to the given window
    window.draw(bar);
}

void FuelBar::updateBarSize()
{
    // Calculate the percentage of current fuel relative to the initial capacity
    float fuelPercentage = currentFuel / initialFuel;

    // Update the size of the fuel bar based on the percentage
    bar.setSize(sf::Vector2f(maxWidth * fuelPercentage, bar.getSize().y));
}