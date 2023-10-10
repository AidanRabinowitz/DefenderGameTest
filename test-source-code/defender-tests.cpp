#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Player.h"
#include "Laser.h"
#include "Lander.h"
#include "Missile.h"
#include "Fuels.h"
#include "FuelBar.h"
#include "GameEntity.h"
#include "Humanoid.h"
#include "CollisionHandler.h"

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
        std::vector<Humanoid> humanoids;        // Create a vector to hold humanoids
        Lander lander(1, humanoids);            // Pass an id and the humanoids container
        sf::Vector2f initialPosition(100, 100); // Set your desired initial position
        lander.reset();
        lander.sprite.setPosition(initialPosition);
        CHECK(lander.getPosition() == initialPosition); // Check if the lander was spawned at the initial position
        lander.update();                                // Move the lander
        CHECK(lander.getPosition() != initialPosition);
    }

    SUBCASE("Lander destruction")
    {
        std::vector<Humanoid> humanoids;   // Create a vector to hold humanoids
        Lander lander(1, humanoids);       // Pass an id and the humanoids container
        CHECK_FALSE(lander.isDestroyed()); // Initially, the lander should not be destroyed
        lander.destroy();
        CHECK(lander.isDestroyed());
    }
}

TEST_CASE("Collision tests")
{
    SUBCASE("Laser and Lander collision")
    {
        std::vector<Humanoid> humanoids; // Create a vector to hold humanoids
        Laser laser;
        Lander lander(1, humanoids); // Pass an id and the humanoids container

        // Set the laser and lander positions to overlap (collision)
        laser.shape.setPosition(100, 100);
        lander.sprite.setPosition(100, 100);

        // Check if there is a collision between the laser and lander
        CHECK(laser.shape.getGlobalBounds().intersects(lander.sprite.getGlobalBounds()));
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

TEST_CASE("Humanoid Initialization")
{
    Humanoid humanoid;

    SUBCASE("Initial State")
    {
        CHECK(humanoid.isDestroyed() == false);
        CHECK(humanoid.isCarried() == false);
        CHECK(humanoid.isTouchingPlayer() == false);
    }

    SUBCASE("Original Position")
    {
        CHECK(humanoid.sprite.getPosition() == sf::Vector2f(0.0f, 0.0f));
    }
}

TEST_CASE("Humanoid Reset")
{
    Humanoid humanoid;
    humanoid.setOriginalPosition(100.0f, 100.0f);
    humanoid.setPosition(200.0f, 200.0f);
    humanoid.setCarried(true);
    humanoid.setFreeFall(true);
    humanoid.reset();

    CHECK(humanoid.getPosition() == sf::Vector2f(100.0f, 100.0f));
    CHECK(humanoid.isCarried() == false);
}

TEST_CASE("Humanoid Passenger Movement")
{
    Humanoid humanoid;
    float initialX = humanoid.getPosition().x;
    float initialY = humanoid.getPosition().y;

    SUBCASE("Move Right")
    {
        humanoid.passengerMovement(10.0f, 0.0f);
        CHECK(humanoid.getPosition().x == initialX + 10.0f);
        CHECK(humanoid.getPosition().y == initialY);
    }

    SUBCASE("Move Left")
    {
        humanoid.passengerMovement(-10.0f, 0.0f);
        CHECK(humanoid.getPosition().x == initialX - 10.0f);
        CHECK(humanoid.getPosition().y == initialY);
    }

    SUBCASE("Move Up")
    {
        humanoid.passengerMovement(0.0f, -10.0f);
        CHECK(humanoid.getPosition().x == initialX);
        CHECK(humanoid.getPosition().y == initialY - 10.0f);
    }

    SUBCASE("Move Down")
    {
        humanoid.passengerMovement(0.0f, 10.0f);
        CHECK(humanoid.getPosition().x == initialX);
        CHECK(humanoid.getPosition().y == initialY + 10.0f);
    }
}
TEST_CASE("Humanoid FreeFall Status")
{
    Player player;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    Humanoid humanoid;
    CHECK_FALSE(humanoid.isFreeFall());
    humanoid.sprite.setPosition(10.0f, 10.0f);
    humanoid.setFreeFall(true);
    CHECK(humanoid.isFreeFall());
    humanoid.update(player.getPosition(), player, window);

    humanoid.setFreeFall(false);
    CHECK_FALSE(humanoid.isFreeFall());
    CHECK_FALSE(humanoid.sprite.getPosition().y == 10.0f);
}
TEST_CASE("Humanoid Collision with Laser")
{
    // Create a humanoid
    Humanoid humanoid;
    humanoid.setPosition(100, 100);         // Set the humanoid's position
    humanoid.setOriginalPosition(100, 100); // Set the original position

    // Create a laser
    Laser laser;
    laser.shape.setPosition(100, 100); // Set the laser's position

    // Check if there is a collision between the humanoid and laser
    CHECK(humanoid.checkCollisionWithLaser(laser) == true);
}

TEST_CASE("Lander-Humanoid Collision")
{
    // Create a vector to hold humanoids
    std::vector<Humanoid> humanoids;

    // Create a Lander and set its position
    Lander lander(1, humanoids);                        // Pass an id and the humanoids container
    sf::Vector2f initialLanderPosition(100.0f, 100.0f); // Set the initial position of the Lander
    lander.reset();
    lander.sprite.setPosition(initialLanderPosition);

    // Create a Humanoid and set its position to collide with the Lander
    Humanoid humanoid;
    sf::Vector2f initialHumanoidPosition(100.0f, 100.0f); // Set the initial position of the Humanoid
    humanoid.setPosition(initialHumanoidPosition.x, initialHumanoidPosition.y);

    // Update the Lander to check for collisions
    lander.update();

    // Check if the Lander is carrying the Humanoid after collision
    CHECK(lander.isCarryingHumanoid());
}

// TEST_CASE("Lander-Humanoid Collision")
// {
//     // Create a Lander and a Humanoid
//     Lander lander(1); // Assuming the lander's ID is 1
//     Humanoid humanoid;

//     // Set positions such that the lander and humanoid collide
//     lander.sprite.setPosition(100, 100);
//     humanoid.setPosition(100, 100);

//     // Initially, the lander should not be carrying the humanoid
//     CHECK_FALSE(lander.isCarryingHumanoid());

//     // Call the collision handling function
//     CollisionHandler collisionHandler;
//     std::vector<Lander> landers = { lander };
//     std::vector<Humanoid> humanoids = { humanoid };
//     collisionHandler.handleLaserLanderCollisions({}, landers, score); // Empty laser vector as it's not relevant here

//     // Check if the lander is carrying the humanoid after the collision
//     CHECK(lander.isCarryingHumanoid());
// }

// TEST_CASE("Lander-Humanoid Collision")
// {
//     // Create a vector of Humanoids and add one Humanoid to it
//     std::vector<Humanoid> humanoids;
//     Humanoid humanoid;
//     humanoids.push_back(humanoid);

//     // Create a Lander with an ID and the vector of Humanoids
//     Lander lander(1, humanoids);

//     // Initially, Lander should not be carrying a Humanoid
//     CHECK_FALSE(lander.isCarryingHumanoid());

//     // Set positions such that they touch but don't collide
//     lander.sprite.setPosition(100, 100); // Position Lander at (100, 100)
//     humanoid.setPosition(100, 200);      // Position Humanoid at (100, 200)

//     // Update the Lander
//     lander.update();

//     // Lander should not be carrying the Humanoid
//     CHECK_FALSE(lander.isCarryingHumanoid());

//     // Set positions such that they collide
//     lander.sprite.setPosition(100, 100); // Position Lander at (100, 100)
//     humanoid.setPosition(100, 100);      // Position Humanoid at (100, 100)

//     // Update the Lander
//     lander.update();

//     // Now, Lander should be carrying the Humanoid
//     CHECK(lander.isCarryingHumanoid());

//     // Update the Lander again (simulate movement)
//     lander.update();

//     // Now, Lander should be moving up
//     CHECK(lander.isMovingUp());
// }

TEST_CASE("Humanoid FreeFall and Player Interaction")
{
    // Create a window for testing (you can adjust the window size)
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");

    // Create a Humanoid and a Player
    Humanoid humanoid;
    Player player;

    // Set up positions for the humanoid and player to touch
    humanoid.setPosition(100, 100);
    player.setPosition(100, 100);

    // Enable free fall for the humanoid
    humanoid.setFreeFall(true);

    // Simulate the player's position and check interaction
    sf::Vector2f playerPosition(100, 100); // Set the player's position to touch the humanoid
    humanoid.update(playerPosition, player, window);

    // Check if the humanoid is touching the player
    CHECK(humanoid.isTouchingPlayer());

    // Check if the humanoid is at the same position as the player
    CHECK(humanoid.getPosition() == player.getPosition());

    // Now, simulate the player's movement
    player.handleMovement(window);

    // Update the humanoid with the player's new position
    playerPosition = player.getPosition();
    humanoid.update(playerPosition, player, window);

    // Check if the humanoid still follows the player's position
    CHECK(humanoid.getPosition() == player.getPosition());
}

TEST_CASE("Humanoid Reset on Touching Bottom")
{
    // Create a window for testing (you can adjust the window size)
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");

    // Create a Humanoid and a Player
    Humanoid humanoid;
    Player player;

    // Set up positions for the humanoid and player to touch
    humanoid.setOriginalPosition(100, 100);
    player.setPosition(100, 100);

    // Enable free fall for the humanoid
    humanoid.setFreeFall(true);

    // Simulate the player's position and check interaction
    sf::Vector2f playerPosition(100, 100); // Set the player's position to touch the humanoid
    humanoid.update(playerPosition, player, window);

    // Check if the humanoid is touching the player
    CHECK(humanoid.isTouchingPlayer());

    // Simulate the player touching the bottom of the window
    player.setPosition(100, window.getSize().y - 10);
    playerPosition = player.getPosition();
    humanoid.update(playerPosition, player, window);

    // Check if the humanoid is no longer touching the player
    CHECK_FALSE(humanoid.isTouchingPlayer());

    // Check if the humanoid's reset function is called
    humanoid.update(playerPosition, player, window);

    // Check if the humanoid is reset to its original position
    CHECK(humanoid.getPosition().x == 100);
}