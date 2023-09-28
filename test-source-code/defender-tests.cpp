#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Player.h"
#include "Laser.h"
#include "Lander.h"
#include "Missile.h"
#include "Fuels.h"
#include "FuelBar.h"

TEST_CASE("Player movement")
{
    Player player;
    sf::Texture texture;

    player.setTexture(texture);

    SUBCASE("Moving up (W key)")
    {
        sf::Vector2f initialPosition = player.getPosition();
        player.move(0, -10); // Assuming -10 moves the player up
        sf::Vector2f newPosition = player.getPosition();
        CHECK(newPosition.y == doctest::Approx(initialPosition.y - 10));
        CHECK(newPosition.x == doctest::Approx(initialPosition.x));
    }

    SUBCASE("Moving left (A key)")
    {
        sf::Vector2f initialPosition = player.getPosition();
        player.move(-10, 0); // Assuming -10 moves the player left
        sf::Vector2f newPosition = player.getPosition();
        CHECK(newPosition.x == doctest::Approx(initialPosition.x - 10));
        CHECK(newPosition.y == doctest::Approx(initialPosition.y));
    }

    SUBCASE("Moving down (S key)")
    {
        sf::Vector2f initialPosition = player.getPosition();
        player.move(0, 10); // Assuming 10 moves the player down
        sf::Vector2f newPosition = player.getPosition();
        CHECK(newPosition.y == doctest::Approx(initialPosition.y + 10));
        CHECK(newPosition.x == doctest::Approx(initialPosition.x));
    }

    SUBCASE("Moving right (D key)")
    {
        sf::Vector2f initialPosition = player.getPosition();
        player.move(10, 0); // Assuming 10 moves the player right
        sf::Vector2f newPosition = player.getPosition();
        CHECK(newPosition.x == doctest::Approx(initialPosition.x + 10));
        CHECK(newPosition.y == doctest::Approx(initialPosition.y));
    }
}
TEST_CASE("Laser firing")
{
    Laser laser;

    SUBCASE("Mouse click fires laser")
    {
        sf::Vector2f startPosition(100, 100);
        sf::Event event;
        event.type = sf::Event::MouseButtonPressed;
        event.mouseButton.button = sf::Mouse::Left;
        sf::Vector2f mousePosition(200, 200); // Set your desired mouse position
        laser.fire(startPosition, mousePosition);
        laser.move();
        CHECK(laser.isFired() == true);
    }
}

TEST_CASE("Lander behavior")
{
    SUBCASE("Lander spawning and movement")
    {
        Lander lander;
        sf::Vector2f initialPosition(100, 100); // Set your desired initial position
        lander.reset();
        lander.getSprite().setPosition(initialPosition);
        CHECK(lander.getPosition() == initialPosition); // Check if the lander was spawned at the initial position
        lander.update();                                // Move the lander
        CHECK(lander.getPosition() != initialPosition);
    }

    SUBCASE("Lander destruction")
    {
        Lander lander;
        CHECK_FALSE(lander.isDestroyed()); // Initially, the lander should not be destroyed
        lander.destroy();
        CHECK(lander.isDestroyed());
    }
}
TEST_CASE("Collision tests")
{
    SUBCASE("Laser and Lander collision")
    {
        Laser laser;
        Lander lander;

        // Set the laser and lander positions to overlap (collision)
        laser.shape.setPosition(100, 100);
        lander.getSprite().setPosition(100, 100);

        // Check if there is a collision between the laser and lander
        CHECK(laser.shape.getGlobalBounds().intersects(lander.getSprite().getGlobalBounds()));
    }
}

TEST_CASE("Fuels class tests")
{
    Fuels fuels; // Create an instance of Fuels for testing

    SUBCASE("Initial state")
    {
        CHECK_FALSE(fuels.isDestroyed()); // Fuels should not be destroyed initially
    }

    SUBCASE("Position and collision tests")
    {
        // Set position and check
        fuels.setPosition(sf::Vector2f(50.0f, 60.0f));
        CHECK(fuels.getPosition() == sf::Vector2f(50.0f, 60.0f));

        // Create a player for collision testing
        Player player;
        player.setPosition(55.0f, 65.0f);

        // Check collision with player
        CHECK(fuels.checkCollisionWithPlayer(player) == true);
        // After collision, check if destroyed
        CHECK(fuels.isDestroyed() == true);
    }

    SUBCASE("Destruction and state change")
    {
        fuels.destroy();
        CHECK(fuels.isDestroyed() == true);
    }
}

TEST_CASE("Player Fuel Tests")
{
    Player player; // Initialize a player object

    SUBCASE("Initial Fuel Levels")
    {
        CHECK(player.hasFuel());                                   // Check if player initially has fuel
        CHECK(player.getCurrentFuel() == doctest::Approx(100.0f)); // Initial current fuel should be 100.0f
        CHECK(player.getTotalFuel() == doctest::Approx(100.0f));   // Initial total fuel should be 100.0f
    }
}

TEST_CASE("FuelBar Class Tests")
{
    SUBCASE("Initial Fuel Bar")
    {
        FuelBar fuelBar(200.0f, 20.0f, 100.0f); // Initialize a FuelBar object

        CHECK(fuelBar.getMaxWidth() == doctest::Approx(200.0f));    // Initial max width should be 200.0f
        CHECK(fuelBar.getCurrentFuel() == doctest::Approx(100.0f)); // Initial current fuel should be 100.0f
    }

    SUBCASE("Fuel Reset")
    {
        FuelBar fuelBar(200.0f, 20.0f, 100.0f); // Initialize a FuelBar object

        // Reduce the fuel bar width
        fuelBar.setFuel(50.0f);

        CHECK(fuelBar.getMaxWidth() == doctest::Approx(200.0f));   // Max width should not change
        CHECK(fuelBar.getCurrentFuel() == doctest::Approx(50.0f)); // Current fuel should be updated

        fuelBar.reset();

        CHECK(fuelBar.getMaxWidth() == doctest::Approx(200.0f));    // After reset, max width should not change
        CHECK(fuelBar.getCurrentFuel() == doctest::Approx(100.0f)); // After reset, current fuel should be 100.0f
    }
}

TEST_CASE("Missile Initialization")
{
    sf::Vector2f initialPosition(10.0f, 20.0f);
    sf::Vector2f targetPosition(50.0f, 60.0f);

    Missile missile(initialPosition, targetPosition);

    SUBCASE("Position and Velocity")
    {
        CHECK(missile.shape.getPosition() == initialPosition);
        CHECK(missile.velocity.x != 0.0f); // Velocity should not be zero
        CHECK(missile.velocity.y != 0.0f);
    }

    SUBCASE("Shape")
    {
        CHECK(missile.shape.getSize() == sf::Vector2f(3, 15));
        CHECK(missile.shape.getFillColor() == sf::Color::Red);
    }
}

TEST_CASE("Missile Movement")
{
    sf::Vector2f initialPosition(10.0f, 20.0f);
    sf::Vector2f targetPosition(50.0f, 60.0f);

    Missile missile(initialPosition, targetPosition);

    SUBCASE("Move")
    {
        sf::Vector2f initialPosition = missile.shape.getPosition();
        missile.move();
        sf::Vector2f newPosition = missile.shape.getPosition();

        CHECK(newPosition != initialPosition); // Check if the missile has moved
    }
}