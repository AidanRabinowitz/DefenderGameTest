#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Player.h"
#include "Laser.h"
#include "Lander.h"
#include "Missile.h"
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