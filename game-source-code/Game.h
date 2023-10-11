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

    /**
     * @brief Construct a new Game object
     * 
     */
    Game();

    /**
     * @brief A function to run the game logic, including handling input, updating game state, and rendering.
     * 
     * @param window A reference to the SFML RenderWindow.
     */
    void run(sf::RenderWindow &window);
    
    /**
     * @brief A function to spawn Landers in the game.
     * 
     */
    void spawnLanders();
    
    /**
     * @brief A function to check if the game is over.
     * 
     * @return true if the game is over, false otherwise.
     */
    bool gameOverStatus();

    /**
     * @brief  A function to draw a text object to the SFML window.
     * 
     * @param window A reference to the SFML RenderWindow.
     * @param text The SFML Text object to be drawn.
     */
    void drawText(sf::RenderWindow &window, const sf::Text &text);

    /**
     * @brief A function to display the current game level.
     * 
     * @param window A reference to the SFML RenderWindow.
     * @param font The font used for rendering the text.
     * @param level The current game level to display.
     */
    void displayLevel(sf::RenderWindow &window, sf::Font &font, int level);
    
    /**
     * @brief A function to handle fuel depletion for the player.
     * 
     * @param player A reference to the Player object.
     */
    void handleFuelDepletion(Player &player);

    /**
     * @brief A function to display the current game score and high score.
     * 
     * @param window A reference to the SFML RenderWindow.
     * @param font The font used for rendering the text.
     * @param score The current game score.
     * @param highScore The high score achieved in the game.
     */
    void displayScore(sf::RenderWindow &window, sf::Font &font, int score, int highScore);

    /**
     * @brief A function to load textures for various game elements, such as screens.
     * 
     */
    void loadScreenTextures();
    
    /**
     * @brief A function to update the game state, including the positions of game objects and collisions.
     * 
     * @param window A reference to the SFML RenderWindow.
     */
    void update(sf::RenderWindow &window);

    /**
     * @brief A function to display the different screens based on the game state.
     * 
     * @param window A reference to the SFML RenderWindow.
     * @param font The font used for rendering the text.
     * @param gameStarted Indicates if the game is started.
     * @param isPauseScreenVisible Indicates if the pause screen is visible
     * @param isGameOver Indicates if the game over screen is visible.
     * @param isWinScreenVisible Indicates if the win screen is visible.
     * @param level The current game level.
     */
    void displayScreen(sf::RenderWindow &window, sf::Font &font, bool gameStarted, bool isPauseScreenVisible, bool isGameOver, bool isWinScreenVisible, int level);

    /**
     * @brief A function to create Humanoid objects.
     * 
     */
    void createHumanoids();

    /**
     * @brief Initialize the number of humans killed in the start to 0.
     * 
     */
    int humansKilled = 0; 

    /**
     * @brief A function to display the count of humans killed on the game screen.
     * 
     * @param window A reference to the SFML RenderWindow.
     * @param font The font used for rendering the text.
     * @param humansKilled The number of humans killed.
     */
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

    /**
     * @brief A function to reset the game to its initial state.
     * 
     */
    void resetGame();

    /**
     * @brief A function to handle user input for the game.
     * 
     * @param window A reference to the SFML RenderWindow.
     */
    void handleInput(sf::RenderWindow &window);

    /**
     * @brief A function to render the game, including game objects, text, and screens.
     * 
     * @param window A reference to the SFML RenderWindow.
     */
    void render(sf::RenderWindow &window);
};