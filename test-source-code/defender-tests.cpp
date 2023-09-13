#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Player.h"
#include "Laser.h"
#include "Lander.h"
#include "Missile.h"
TEST_CASE("Player movement")
{
    Player player;
    sf::Texture texture; // You need to create a texture or use a mocked one

    // Initialize the player with the texture
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
        sf::Vector2f startPosition(100, 100); // Set your desired starting position

        // Simulate a mouse click event
        sf::Event event;
        event.type = sf::Event::MouseButtonPressed;
        event.mouseButton.button = sf::Mouse::Left;

        // Call the Laser::fire method with the mouse position
        sf::Vector2f mousePosition(200, 200); // Set your desired mouse position
        laser.fire(startPosition, mousePosition);

        // Update the laser
        laser.move();

        // Check if the laser was fired
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

        // Check if the lander was spawned at the initial position
        CHECK(lander.getPosition() == initialPosition);

        // Move the lander
        lander.update();

        // Check if the lander has moved (position changed)
        CHECK(lander.getPosition() != initialPosition);
    }

    SUBCASE("Lander destruction")
    {
        Lander lander;

        // Initially, the lander should not be destroyed
        CHECK_FALSE(lander.isDestroyed());

        // Destroy the lander
        lander.destroy();

        // Check if the lander is destroyed
        CHECK(lander.isDestroyed());
    }
}
TEST_CASE("Collision tests")
{
    // SUBCASE("Player and Lander collision")
    // {
    //     Player player;
    //     Lander lander;

    //     // Set the player's position
    //     player.setPosition(100, 100);
    //     lander.getPosition() = player.getPosition();
    //     // Reset the lander's position (assuming it's out of collision by default)
    //     lander.reset();
    //     lander.update();

    //     // Check if there is a collision between the player and lander
    //     CHECK(player.getGlobalBounds().intersects(lander.getSprite().getGlobalBounds()));
    // }

    // SUBCASE("Missile and Player collision")
    // {
    //     Missile missile(sf::Vector2f(100, 100), sf::Vector2f(101, 101)); // Set missile and player positions to overlap (collision)
    //     Player player;
    //     player.setPosition(100, 100);

    //     // Set the position of the missile's shape
    //     missile.shape.setPosition(100, 100);

    //     // Check if there is a collision between the missile and player
    //     CHECK(missile.shape.getGlobalBounds().intersects(player.getGlobalBounds()));
    // }

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