#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#pragma once

#include <SFML/Graphics.hpp>

enum class GameState {
    SplashScreen,
    Gameplay,
    PauseScreen,
    WinScreen,
    ExitScreen,
    GameOver,
    GameWin,
    GameRunning,
    // Add other game states as needed
};


class ScreenManager {
public:
    ScreenManager();

    void handleInput(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

    void setGameState(GameState newState);
    void initialize();
    void render(sf::RenderWindow& window);  // Corrected method name
    void setCurrentScreen(GameState newState); // Corrected method name
    GameState getCurrentScreen() const;      // Corrected method name
    // Reset the game state and variables to their initial values
    void resetGame();

private:
    GameState currentGameState;
    GameState currentScreen;
    std::map<GameState, sf::Texture> screenTextures;
    int score;
    int highScore;
    bool gameStarted;
    bool isSplashScreenVisible;
    bool isPauseScreenVisible;
    bool isGameOver;
    bool isWinScreenVisible;
    int level;
    int previousLevelScore;
    int humansKilled;

    // Add other game-specific variables as needed
};
#endif