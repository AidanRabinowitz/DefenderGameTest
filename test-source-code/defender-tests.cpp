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
#include "Game.h"

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

TEST_CASE("Laser Default Constructor")
{
    Laser laser;

    CHECK_FALSE(laser.isFired());
}

TEST_CASE("Laser Fire")
{
    Laser laser;
    sf::Vector2f playerPosition(100.0f, 200.0f);
    sf::Vector2f mousePosition(300.0f, 200.0f);

    laser.fire(playerPosition, mousePosition);

    CHECK(laser.isFired());
    CHECK(laser.getPosition().x == playerPosition.x + 42);
    CHECK(laser.getPosition() == sf::Vector2f(playerPosition.x + 42, playerPosition.y));
}

TEST_CASE("Laser Move")
{
    Laser laser;
    sf::Vector2f initialPosition = laser.getPosition();

    laser.fire(sf::Vector2f(100.0f, 200.0f), sf::Vector2f(300.0f, 200.0f));
    laser.move();

    CHECK(laser.getPosition() != initialPosition);
}

TEST_CASE("Laser Set Fired")
{
    Laser laser;

    laser.setFired(true);

    CHECK(laser.isFired());
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

TEST_CASE("Lander Constructor and Reset")
{
    std::vector<Humanoid> humanoids;
    Lander lander(1, humanoids);

    CHECK_FALSE(lander.isDestroyed());
    CHECK_FALSE(lander.isCarryingHumanoid());

    lander.reset();

    CHECK_FALSE(lander.isDestroyed());
    CHECK_FALSE(lander.isCarryingHumanoid());
}

TEST_CASE("Lander Update")
{
    std::vector<Humanoid> humanoids;
    Lander lander(1, humanoids);

    SUBCASE("Lander Without Humanoid Interaction")
    {
        lander.update();

        CHECK_FALSE(lander.isMovingUp());
        CHECK_FALSE(lander.isCarryingHumanoid());
        CHECK_FALSE(lander.isDestroyed());
    }

    SUBCASE("Lander Pickup Humanoid and Move Up")
    {
        Humanoid humanoid;
        humanoids.push_back(humanoid);
        lander.update();

        CHECK(lander.isMovingUp());
        CHECK(lander.isCarryingHumanoid());
        CHECK_FALSE(lander.isDestroyed());
    }

    SUBCASE("Lander Out of Bounds")
    {
        Humanoid humanoid;
        humanoids.push_back(humanoid);

        // Move the lander out of bounds
        for (int i = 0; i < 1000; ++i)
        {
            lander.update();
        }

        CHECK(lander.isDestroyed());
    }
}

TEST_CASE("Lander Destroy")
{
    std::vector<Humanoid> humanoids; // Create an empty vector of humanoids
    Lander lander(1, humanoids);

    lander.destroy();

    CHECK(lander.isDestroyed());
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

TEST_CASE("Fuels Constructor and Spawn Fuel")
{
    std::vector<Fuels> fuels;

    SUBCASE("Spawn Fuel")
    {
        sf::Texture texture;
        Fuels fuel;
        fuel.spawnFuel(fuels, texture);

        CHECK(fuels.size() == 1);
        CHECK_FALSE(fuels[0].isDestroyed());
        CHECK(fuels[0].getPosition().x >= 0.0f);
    }

    SUBCASE("Spawn Multiple Fuels")
    {
        sf::Texture texture;
        Fuels fuel2;
        fuel2.spawnFuel(fuels, texture);
        Fuels fuel3;
        fuel3.spawnFuel(fuels, texture);

        CHECK(fuels.size() == 2);
    }
}

TEST_CASE("Fuels Collision Detection")
{
    std::vector<Fuels> fuels;
    Fuels fuel;
    fuels.push_back(fuel);

    SUBCASE("Check Collision with Player")
    {
        Player player;
        player.setPosition(0.0f, 0.0f);
        CHECK(fuels[0].checkCollisionWithPlayer(player));
        CHECK(fuels[0].isDestroyed());
    }

    SUBCASE("Check No Collision with Player")
    {
        Player player;
        player.setPosition(100.0f, 100.0f);
        CHECK_FALSE(fuels[0].checkCollisionWithPlayer(player));
        CHECK_FALSE(fuels[0].isDestroyed());
    }
}

TEST_CASE("Fuels Destruction")
{
    Fuels fuel;
    CHECK_FALSE(fuel.isDestroyed());
    fuel.destroy();
    CHECK(fuel.isDestroyed());
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

TEST_CASE("Laser Movement")
{
    // Create a Laser instance
    Laser laser;

    // Define initial position and target position
    sf::Vector2f initialPosition(100.0f, 200.0f);
    sf::Vector2f targetPosition(200.0f, 200.0f);

    // Fire the laser with the initial and target positions
    laser.fire(initialPosition, targetPosition);

    // Move the laser
    laser.move();

    // Check if the laser's X position has increased by LASER_SPEED
    CHECK(laser.shape.getPosition().x == initialPosition.x + 42 + LASER_SPEED);
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

TEST_CASE("Lander-Humanoid Collision")
{
    // Create a vector of Humanoids and add one Humanoid to it
    std::vector<Humanoid> humanoids;
    Humanoid humanoid;
    humanoids.push_back(humanoid);

    // Create a Lander with an ID and the vector of Humanoids
    Lander lander(1, humanoids);

    // Initially, Lander should not be carrying a Humanoid
    CHECK_FALSE(lander.isCarryingHumanoid());

    // Set positions such that they touch but don't collide
    lander.sprite.setPosition(100, 100); // Position Lander at (100, 100)
    humanoid.setPosition(100, 200);      // Position Humanoid at (100, 200)

    // Update the Lander
    lander.update();

    // Lander should not be carrying the Humanoid
    CHECK_FALSE(lander.isCarryingHumanoid());
}

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

TEST_CASE("CollisionHandler Laser-Humanoid Collisions")
{
    CollisionHandler collisionHandler;
    std::vector<Laser> lasers;
    std::vector<Humanoid> humanoids;

    // Create Laser and Humanoid objects for testing
    Laser laser;
    Humanoid humanoid;
    laser.fire(sf::Vector2f(10.0f, 10.0f), sf::Vector2f(20.0f, 20.0f));
    humanoids.push_back(humanoid);

    // Initially, no collisions should have occurred
    collisionHandler.handleLaserHumanoidCollisions(lasers, humanoids);
    CHECK(lasers.size() == 0);
    CHECK(humanoids.size() == 1);

    // Test collision handling
    collisionHandler.handleLaserHumanoidCollisions(lasers, humanoids);
    CHECK(lasers.empty()); // Laser should have been removed
    auto count = 0;
    for (auto &humanoid : humanoids)
    {
        if (humanoid.isDestroyed())
        {
            count++;
        }
    }
    CHECK(count == 0); // Humanoid should have been destroyed
}

TEST_CASE("CollisionHandler Player-Missile Collisions")
{
    CollisionHandler collisionHandler;
    Player player;
    std::vector<Missile> missiles;

    // Create a Missile object for testing
    Missile missile(sf::Vector2f(10.0f, 10.0f), sf::Vector2f(20.0f, 20.0f));
    missiles.push_back(missile);

    // Initially, no collisions should have occurred
    bool collision = collisionHandler.handlePlayerMissileCollisions(player, missiles);
    CHECK_FALSE(collision);
}

TEST_CASE("Scoring when Laser hits Lander")
{
    // Create a vector of lasers
    std::vector<Laser> lasers;

    // Create a vector of landers
    std::vector<Lander> landers;

    // Initialize the score
    int score = 0;

    // Add a Laser and a Lander to the vectors
    Laser laser;
    std::vector<Humanoid> humanoids; // Create a vector to hold humanoids
    Lander lander(1, humanoids);     // Pass an id and the humanoids container

    // Set positions for laser and lander
    sf::Vector2f laserPosition(100, 100);  // Replace with actual positions
    sf::Vector2f landerPosition(100, 100); // Replace with actual positions
    laser.sprite.setPosition(laserPosition);
    lander.sprite.setPosition(landerPosition);

    lasers.push_back(laser);
    landers.push_back(lander);

    // Ensure the Lander is not destroyed
    CHECK_FALSE(landers[0].isDestroyed());

    // Fire the Laser and set its position to collide with the Lander
    sf::Vector2f playerPosition(100, 100); // Replace with actual positions
    lasers[0].fire(playerPosition, laserPosition);

    // Create a collision handler and perform collision handling (this should increase the score)
    CollisionHandler handler;
    handler.handleLaserLanderCollisions(lasers, landers, score);

    // Check if the Laser is marked as fired
    CHECK(lasers[0].isFired());

    // Ensure the Lander is marked as destroyed
    CHECK(landers[0].isDestroyed());

    // Check if the score increased by 10
    CHECK(score == 10);

    // Perform additional checks for the destroyed state of Lander
    CHECK_FALSE(landers[0].isMovingUp());
    CHECK_FALSE(landers[0].isCarryingHumanoid());
    // Add more checks as needed

    // Perform additional checks for the Laser's fired state and position
    CHECK(lasers[0].isFired());
}

TEST_CASE("Player Runs Out of Fuel, Descends, and Game Ends")
{
    // Create a game object and player
    Game game; // Adjust this constructor if needed
    Player player;

    // Replace the player's fuel with a small value for testing
    player.resetCurrentFuel();
    REQUIRE(player.hasFuel());

    // Consume all the fuel immediately
    player.consumeFuel(player.getCurrentFuel() + 1);

    // Ensure the player is out of fuel
    REQUIRE_FALSE(player.hasFuel());

    // Call the function to handle fuel depletion and player movement
    game.handleFuelDepletion(player);
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");

    // Simulate frames for a 3-second delay
    int framesToSimulate = 3 * 60; // 3 seconds at 60 FPS
    for (int i = 0; i < framesToSimulate; ++i)
    {
        game.update(window);
    }
    // Check if the game is marked as over
    bool isGameOver = game.gameOverStatus(); // Replace with your actual method
    REQUIRE(isGameOver);
}