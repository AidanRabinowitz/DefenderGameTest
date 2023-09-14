// game.h
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "GameConstants.h"
#include "Lander.h"
#include "Missile.h"
#include "Laser.h"
#include "Player.h"

// #include
class Game
{
public:
    Game();

    void run(sf::RenderWindow &window);

private:
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
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    Player player;
    sf::Texture playerTexture;
    std::vector<Lander> landers;
    std::vector<Missile> missiles;
    std::vector<Laser> lasers;
    sf::Clock spawnTimer;
    sf::Clock missileTimer;
    sf::Font font;
    void resetGame();
    void handleInput(sf::RenderWindow &window);
    void update();
    void render(sf::RenderWindow &window);
};