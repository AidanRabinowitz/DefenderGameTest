#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
// #include "game.h"

// TEST_CASE("Player movement")
// {
//     // Create a Game object
//     Game game;

//     // Create a RenderWindow object for testing
//     sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");

//     SUBCASE("Move up (W key)")
//     {
//         // Get the initial position of the player
//         sf::Vector2f initialPosition = game.player.getPosition();

//         // Simulate pressing the W key
//         sf::Event event;
//         event.type = sf::Event::KeyPressed;
//         event.key.code = sf::Keyboard::W;
//         window.pollEvent(event);

//         // Handle input using the RenderWindow
//         game.handleInput(window);

//         // Get the player's position after moving up
//         sf::Vector2f newPosition = game.player.getPosition();

//         // Check if the player moved up (Y coordinate decreased)
//         CHECK(newPosition.y > initialPosition.y);
//     }

//     // Repeat the same approach for other movement tests
//     // ...

//     // Close the RenderWindow after all tests
//     window.close();
// }
