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
#include "CollisionHandler.h"
class Game : public GameEntity
{
public:
    Game();
    void run(sf::RenderWindow &window);
    void spawnLanders();
    // Function to display a text object
    void drawText(sf::RenderWindow &window, const sf::Text &text);
    void displayLevel(sf::RenderWindow &window, sf::Font &font, int level);

    // Function to display the score and high score
    void displayScore(sf::RenderWindow &window, sf::Font &font, int score, int highScore);
    void loadScreenTextures();

    // Function to display different screens
    void update(sf::RenderWindow &window);

    void displayScreen(sf::RenderWindow &window, sf::Font &font, bool gameStarted, bool isPauseScreenVisible, bool isGameOver, bool isWinScreenVisible, int level);
    void createHumanoids();
    int humansKilled = 0; // Initialize the number of humans killed in the start to 0
    void displayHumansKilled(sf::RenderWindow &window, sf::Font &font, int humansKilled);

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
    sf::Texture playerTexture;
    sf::Sprite backgroundSprite;
    Player player;
    std::vector<Lander> landers;
    std::vector<Missile> missiles;
    std::vector<Laser> lasers;
    std::vector<Fuels> fuels;
    sf::Clock spawnTimer;
    sf::Clock spawnHumanoidTimer;
    sf::Clock missileTimer;
    sf::Clock frameClock;
    sf::Clock fuelSpawnTimer;
    sf::Font font;
    void resetGame();
    void handleInput(sf::RenderWindow &window);
    void render(sf::RenderWindow &window);
};