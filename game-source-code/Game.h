// game.h
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "GameConstants.h"
#include "Lander.h"
#include "Missile.h"
#include "Laser.h"
#include "Player.h"
#include <cmath>
#include <limits>
#include "FuelBar.h"
#include "Fuels.h"
#include "Humanoid.h"
// #include
class Game
{
public:
    Game();
    void run(sf::RenderWindow &window);
    void spawnLanders();
    // Function to display a text object
    void drawText(sf::RenderWindow &window, const sf::Text &text);

    // Function to display the score and high score
    void displayScore(sf::RenderWindow &window, sf::Font &font, int score, int highScore);

    // Function to display different screens
    void displayScreen(sf::RenderWindow &window, sf::Font &font, bool gameStarted, bool isPauseScreenVisible, bool isGameOver, bool isWinScreenVisible, int level);

private:
    static int nextLanderId; // Static variable to track the next available id for Landers
    std::vector<Humanoid> humanoids;
    sf::Texture humanoidTexture;
    bool isLanderAttached;
    FuelBar fuelBar;
    int previousLevelScore;
    int level;
    int score;
    int highScore;
    bool gameStarted;
    bool quitConfirmation;
    bool isSplashScreenVisible;
    bool isPauseScreenVisible;
    bool isWinScreenVisible;
    bool isGameOver;
    sf::Texture landerTexture;
    sf::Texture fuelsTexture;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    Player player;
    sf::Texture playerTexture;
    std::vector<Lander> landers;
    std::vector<Missile> missiles;
    std::vector<Laser> lasers;
    std::vector<Fuels> fuels;
    sf::Sprite fuelsSprite;
    sf::Sprite humanoidSprite;
    sf::Clock spawnTimer;
    sf::Clock spawnHumanoidTimer;
    sf::Clock missileTimer;
    sf::Clock frameClock; // Add this line to declare frameClock
    sf::Clock fuelSpawnTimer;

    sf::Font font;
    void resetGame();
    void handleInput(sf::RenderWindow &window);
    void update();
    void render(sf::RenderWindow &window);
};