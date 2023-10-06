#include "ScreenManager.h"

ScreenManager::ScreenManager()
    : currentGameState(GameState::SplashScreen),
      score(0),
      highScore(0),
      gameStarted(false),
      isSplashScreenVisible(true),
      isPauseScreenVisible(false),
      isGameOver(false),
      isWinScreenVisible(false),
      level(1),
      previousLevelScore(0),
      humansKilled(0) {
    // Load textures for each screen
    sf::Texture splashScreenTexture;
    if (!splashScreenTexture.loadFromFile("resources/SplashScreen.jpeg")) {
        // Handle loading error
    }
    screenTextures[GameState::SplashScreen] = splashScreenTexture;

    sf::Texture pauseScreenTexture;
    if (!pauseScreenTexture.loadFromFile("resources/GamePaused.jpeg")) {
        // Handle loading error
    }
    screenTextures[GameState::PauseScreen] = pauseScreenTexture;

    sf::Texture gameOverTexture;
    if (!gameOverTexture.loadFromFile("resources/YouDied.jpeg")) {
        // Handle loading error
    }
    screenTextures[GameState::GameOver] = gameOverTexture;

    sf::Texture gameWinTexture;
    if (!gameWinTexture.loadFromFile("resources/YouWin.jpeg")) {
        // Handle loading error
    }
    screenTextures[GameState::GameWin] = gameWinTexture;

    // Load other screen textures as needed
}

// Implementation of setCurrentScreen function
void ScreenManager::setCurrentScreen(GameState newState) {
    // Update the current screen state
    currentScreen = newState;
    // You can add additional logic here if needed...
}
void ScreenManager::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }

    if (currentGameState == GameState::SplashScreen) {
        // Handle input for the splash screen
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            setGameState(GameState::GameRunning);
        }
    } else if (currentGameState == GameState::PauseScreen) {
        // Handle input for the pause screen
        // For example, resume the game on key press
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            setGameState(GameState::GameRunning);
        }
    } else if (currentGameState == GameState::GameOver) {
        // Handle input for the game over screen
        // For example, restart the game on key press
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y)) {
            setGameState(GameState::GameRunning);
            // Add code to reset the game here
            resetGame();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N)) {
            window.close(); // Close the window
        }
    } else if (currentGameState == GameState::GameWin) {
        // Handle input for the game win screen
        // For example, proceed to the next level on key press
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y)) {
            // Add code to proceed to the next level here
            // You can set a new game state or level state
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N)) {
            window.close(); // Close the window
        }
    }
}

void ScreenManager::draw(sf::RenderWindow& window) {
    // Clear the window
    window.clear();

    // Draw the appropriate screen based on the current game state
    sf::Sprite screenSprite(screenTextures[currentGameState]);
    window.draw(screenSprite);

    // Display the contents of the window
    window.display();
}
void ScreenManager::initialize()
{
    currentGameState = GameState::SplashScreen; // Use the correct variable name
}

void ScreenManager::setGameState(GameState newState)
{
    currentGameState = newState; // Use the correct variable name
}

GameState ScreenManager::getCurrentScreen() const
{
    return currentGameState; // Use the correct variable name
}
// Reset the game state and variables to their initial values
void ScreenManager::resetGame() {
    score = 0;
    highScore = 0;
    gameStarted = false;
    isSplashScreenVisible = true;
    isPauseScreenVisible = false;
    isGameOver = false;
    isWinScreenVisible = false;
    level = 1;
    previousLevelScore = 0;
    humansKilled = 0;
    // Reset other game-specific variables here
}
