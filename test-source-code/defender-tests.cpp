#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iostream>

// // Define your game objects and functions here.
// struct Player
// {
//     sf::RectangleShape shape;
// };

// struct Missile
// {
//     sf::RectangleShape shape;
// };

// struct Lander
// {
//     sf::RectangleShape shape;
//     bool isDestroyed;
// };
// struct Laser
// {
//     sf::RectangleShape shape;
// };

// bool isGameOver = false; // A global variable to simulate game over state

// // Function to check collision between player ship and missiles
// bool checkPlayerMissileCollision(const Player &player, const std::vector<Missile> &missiles)
// {
//     for (const auto &missile : missiles)
//     {
//         if (missile.shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
//         {
//             return true;
//         }
//     }
//     return false;
// }

// // Function to check collision between player ship and enemy landers
// bool checkPlayerLanderCollision(const Player &player, const std::vector<Lander> &landers)
// {
//     for (const auto &lander : landers)
//     {
//         if (!lander.isDestroyed && lander.shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
//         {
//             return true;
//         }
//     }
//     return false;
// }

// // Function to check collision between missiles and enemy landers
// void checkMissileLanderCollision(std::vector<Missile> &missiles, std::vector<Lander> &landers, int &score)
// {
//     for (size_t i = 0; i < missiles.size(); i++)
//     {
//         for (size_t j = 0; j < landers.size(); j++)
//         {
//             if (!landers[j].isDestroyed && missiles[i].shape.getGlobalBounds().intersects(landers[j].shape.getGlobalBounds()))
//             {
//                 landers[j].isDestroyed = true;
//                 missiles.erase(missiles.begin() + i);
//                 i--;
//                 score += 10; // Increase the score when a lander is destroyed
//                 break;       // No need to check further missiles for this lander
//             }
//         }
//     }
// }

// // Function to check collision between lasers and enemy landers
// void checkLaserLanderCollision(std::vector<Laser> &lasers, std::vector<Lander> &landers, int &score)
// {
//     for (size_t i = 0; i < lasers.size(); i++)
//     {
//         for (size_t j = 0; j < landers.size(); j++)
//         {
//             if (!landers[j].isDestroyed && lasers[i].shape.getGlobalBounds().intersects(landers[j].shape.getGlobalBounds()))
//             {
//                 landers[j].isDestroyed = true;
//                 lasers.erase(lasers.begin() + i);
//                 i--;
//                 score += 10; // Increase the score when a lander is destroyed
//                 break;       // No need to check further lasers for this lander
//             }
//         }
//     }
// }

// TEST_CASE("Collision Tests")
// {
//     Player player;
//     player.shape.setSize(sf::Vector2f(50, 50));
//     player.shape.setPosition(100, 100);

//     std::vector<Missile> missiles;
//     std::vector<Lander> landers;
//     int score = 0;

//     // Initialize missiles, landers, and player as needed for the test scenarios.

//     SUBCASE("Player ship collision with missiles")
//     {
//         Missile missile;
//         missile.shape.setSize(sf::Vector2f(5, 20));
//         missile.shape.setPosition(100, 100); // Position it to collide with player
//         missiles.push_back(missile);

//         CHECK(checkPlayerMissileCollision(player, missiles) == true);
//     }

//     SUBCASE("Player ship collision with enemy landers")
//     {
//         Lander lander;
//         lander.shape.setSize(sf::Vector2f(30, 30));
//         lander.shape.setPosition(100, 100); // Position it to collide with player
//         landers.push_back(lander);

//         CHECK(checkPlayerLanderCollision(player, landers) == true);
//     }

//     SUBCASE("Missiles collision with enemy landers")
//     {
//         Missile missile;
//         missile.shape.setSize(sf::Vector2f(5, 20));
//         missile.shape.setPosition(100, 100); // Position it to collide with lander
//         missiles.push_back(missile);

//         Lander lander;
//         lander.shape.setSize(sf::Vector2f(30, 30));
//         lander.shape.setPosition(100, 100); // Position it to collide with missile
//         landers.push_back(lander);

//         int initialScore = score;
//         checkMissileLanderCollision(missiles, landers, score);

//         CHECK(score == initialScore + 10);
//         CHECK(landers[0].isDestroyed == true);
//     }

//     SUBCASE("Lasers hitting enemy landers")
//     {
//         Laser laser;
//         laser.shape.setSize(sf::Vector2f(5, 20));
//         laser.shape.setPosition(100, 100); // Position it to collide with lander
//         std::vector<Laser> lasers = {laser};

//         Lander lander;
//         lander.shape.setSize(sf::Vector2f(30, 30));
//         lander.shape.setPosition(100, 100); // Position it to collide with laser
//         landers.push_back(lander);

//         int initialScore = score;
//         checkLaserLanderCollision(lasers, landers, score);

//         CHECK(score == initialScore + 10);
//         CHECK(landers[0].isDestroyed == true);
//     }
// }
