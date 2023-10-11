#include "game.h"
#include "GameEntity.h"
#include <iostream>
Game::Game()
    : score(0), highScore(0), gameStarted(false),
      quitConfirmation(false), isSplashScreenVisible(true),
      isPauseScreenVisible(false), isWinScreenVisible(false), isGameOver(false),
      level(1), previousLevelScore(0), fuelBar(200.0f, 20.0f, 100.f), humansKilled(0)
{
    // Load textures in the game constructor, and check for loading failure, so they are available for setting when game objects are made
    if (!backgroundTexture.loadFromFile("resources/background.jpg"))
    {
        std::cout << "Error loading background texture" << std::endl;
    }
    // Set background texture, so it is available as soon as the game starts.
    backgroundSprite.setTexture(backgroundTexture);
    if (!font.loadFromFile("resources/sansation.ttf"))
    {
        std::cout << "Error loading font" << std::endl;
    }
    if (!humanoidTexture.loadFromFile("resources/humanoid.png"))
    {
        std::cout << "Error loading humanoid texture" << std::endl;
    }
    if (!landerTexture.loadFromFile("resources/landerShip.png"))
    {
        std::cout << "Error loading lander texture" << std::endl;
    }
    if (!fuelsTexture.loadFromFile("resources/fuel.png"))
    {
        std::cout << "Error loading fuels texture" << std::endl;
    }
    createHumanoids();
}
void Game::run(sf::RenderWindow &window)
{
    handleInput(window);
    update(window);
    render(window);
}

void Game::resetGame()
{
    // Reset player position and fuel
    player.setPosition(WINDOW_WIDTH / 2 - 25, WINDOW_HEIGHT - 60);
    player.resetCurrentFuel();
    // Clear the arrays of players and missiles and landers and fuels and humanoids on the window
    landers.clear();
    missiles.clear();
    lasers.clear();
    fuelBar.reset();
    fuels.clear();
    humanoids.clear(); // Reset all the humanoid objects in the vector
    createHumanoids(); // Re-create  the humanoids after resetting them
    level = 1;
}

void Game::createHumanoids()
{
    for (int i = 0; i < 5; i++)
    {
        Humanoid humanoid;
        // Calculate the x position with spacing multiplier
        float xPos = 100 + static_cast<float>(i * 100);
        humanoid.sprite.setTexture(humanoidTexture);
        // Calculate the y position at the bottom of the window
        float yPos = static_cast<float>(WINDOW_HEIGHT - 10 - humanoid.sprite.getGlobalBounds().height);
        humanoid.setOriginalPosition(xPos, yPos); // Store the original position
        humanoid.setPosition(xPos, yPos);
        humanoids.push_back(humanoid);
    }
}

void Game::handleInput(sf::RenderWindow &window)
{
    sf::Event event;
    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    sf::Vector2f playerCenter = player.getPosition() + sf::Vector2f(player.getGlobalBounds().width / 2, player.getGlobalBounds().height / 2);
    sf::Vector2f rightScale(0.1f, 0.1f); // Set scale factors for X and Y uniformly
    sf::Vector2f leftScale(-0.1f, 0.1f); // Swap direction
    if (mousePosition.x > playerCenter.x)
    {
        player.setScale(rightScale); // Fire laser to the right
    }
    else
    {
        player.setScale(leftScale); // Flip horizontally by setting X scale to negative
    }
    if (!gameStarted && !isPauseScreenVisible && !isGameOver && !isWinScreenVisible)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {
            gameStarted = true;
            isSplashScreenVisible = false;
            score = 0; // Reset the score when the game starts
        }
    }
    else if (gameStarted && !isPauseScreenVisible && !isGameOver && !isWinScreenVisible)
    {
        int oldScore = score; // Check if the player has won, ending the game, unless another level is chosen.

        if (score >= previousLevelScore + 100)
        {
            isWinScreenVisible = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            isPauseScreenVisible = true;
        }
    }
    else if (isPauseScreenVisible)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y))
        {
            isPauseScreenVisible = false;
            gameStarted = false;
            if (score > highScore)
            {
                highScore = score; // Save the highscore
            }
            score = 0;
            resetGame();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N))
        {
            isPauseScreenVisible = false;
        }
    }
    // Handle input for game over screen
    else if (isWinScreenVisible)
    {
        gameStarted = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y)) // Continue the next level
        {
            isWinScreenVisible = false;
            gameStarted = true;
            level++;
            previousLevelScore = score;
            gameStarted = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N)) // Restart a new game

        {
            isWinScreenVisible = false;
            isSplashScreenVisible = true;
            resetGame();
            score = 0;
            previousLevelScore = 0;
            level = 1;
        }
    }
    else if (isGameOver)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y))
        {
            isGameOver = false;
            gameStarted = true;
            isSplashScreenVisible = false;
            if (score > highScore)
            {
                highScore = score;
            }
            score = 0;
            previousLevelScore = 0;
            level = 1;
            resetGame();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N))
        {
            gameStarted = false;
            isSplashScreenVisible = true;
            resetGame();
            window.close();
        }
    }
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                Laser laser;
                laser.fire(player.getPosition(), mousePosition);
                lasers.push_back(laser);
            }
        }
    }
    player.handleMovement(window);
}

int Game::nextLanderId = 1;
void Game::spawnLanders()
{
    if (spawnTimer.getElapsedTime().asMilliseconds() > SPAWN_INTERVAL)
    {
        Lander newLander(nextLanderId, humanoids); // Pass the 'humanoids' container
        float xPos = static_cast<float>(rand() % static_cast<int>(WINDOW_WIDTH - newLander.sprite.getGlobalBounds().width));
        newLander.sprite.setPosition(sf::Vector2f(xPos, -newLander.sprite.getGlobalBounds().height));
        newLander.sprite.setTexture(landerTexture);
        landers.push_back(newLander);
        spawnTimer.restart();
        nextLanderId++; // Increment the id for the next Lander
    }
}

void Game::update(sf::RenderWindow &window)
{
    if (gameStarted && !isPauseScreenVisible && !isGameOver)
    {
        // Update the Humanoid objects
        for (auto &humanoid : humanoids)
        {
            humanoid.update(player.getPosition(), player, window);
            if (humanoid.humansKilled >= 5)
            {
                isGameOver = true; // Set isGameOver to true when humansKilled reaches 5
                break;             // Exit the loop since the game is over
            }
            humanoid.removeDestroyed(humanoids); // Remove the humanoid sprites once they have been destroyed
        }
        for (Lander &lander : landers)
        {
            lander.update(); // Update lander position and check for destruction
        }
        spawnLanders(); // SpawnLanders to call the lander spawning function
        for (size_t i = 0; i < landers.size(); i++)
        {
            if (!landers[i].isDestroyed())
            {
                // Lander movement and bounds checks are now handled by the Lander class
                landers[i].update();
            }
        }
        if (fuelSpawnTimer.getElapsedTime().asMilliseconds() > FUEL_SPAWN_INTERVAL)
        {
            // Spawn Fuels
            Fuels fuelCan;
            fuelCan.spawnFuel(fuels, fuelsTexture);
            fuelSpawnTimer.restart();
        }
        for (auto it = fuels.begin(); it != fuels.end();)
        {
            if (it->checkCollisionWithPlayer(player))
            {
                it = fuels.erase(it);      // Collision with fuel detected, remove the fuel
                player.resetCurrentFuel(); // Reset player's current fuel to 100.0f
                fuelBar.reset();           // Reset the fuel bar
            }
            else
            {
                ++it;
            }
        }
        fuelBar.setFuel(player.getCurrentFuel());
        // fuelBar.update();
        float deltaTime = frameClock.restart().asSeconds();
        player.consumeFuel(deltaTime);
        if (player.getCurrentFuel() <= 0)
        {
            player.move(0.0f, 4.0f);
            if (player.getPosition().y > WINDOW_HEIGHT - 60)
                isGameOver = true;
        }

        // Fire Missiles from Landers towards the player's ship after the desired interval
        for (size_t i = 0; i < landers.size(); i++)
        {
            if (missileTimer.getElapsedTime().asMilliseconds() > MISSILE_INTERVAL)
            {
                for (size_t i = 0; i < landers.size(); i++)
                {
                    if (!landers[i].isDestroyed())
                    {
                        missiles.push_back(Missile(landers[i].getPosition(), player.getPosition()));
                    }
                }
                missileTimer.restart();
            }
        }

        // Move and draw missiles
        for (size_t i = 0; i < missiles.size(); i++)
        {
            missiles[i].move();
        }

        // Move Lasers
        for (size_t i = 0; i < lasers.size(); i++)
        {
            lasers[i].shape.move(lasers[i].velocity);
        }

        CollisionHandler collisionHandler; // Create an instance of CollisionHandler to encapsulate collision checks
        // Handle laser-lander collisions
        collisionHandler.handleLaserLanderCollisions(lasers, landers, score);
        // Handle laser-humanoid collisions
        collisionHandler.handleLaserHumanoidCollisions(lasers, humanoids);
        // Handle player-lander collisions
        if (collisionHandler.handlePlayerLanderCollisions(player, landers))
        {
            isGameOver = true;
        }
        // Handle player-missile collisions
        if (collisionHandler.handlePlayerMissileCollisions(player, missiles))
        {
            isGameOver = true;
        }
    }
}

void Game::render(sf::RenderWindow &window) // Rendering the game shapes and sprites
{
    window.clear();
    window.draw(backgroundSprite);
    player.render(window);

    for (auto &humanoid : humanoids)
    {
        humanoid.render(window);
    }

    window.draw(player);
    for (auto &fuelCan : fuels)
    {
        fuelCan.render(window);
    }
    // Draw Landers using the render function from Lander
    for (auto &lander : landers)
    {
        if (!lander.isDestroyed())
        {
            lander.render(window);
        }
    }

    // Draw Missiles
    for (const auto &missile : missiles)
    {
        window.draw(missile.shape);
    }

    // Draw Lasers
    for (const auto &laser : lasers)
    {
        window.draw(laser.shape);
    }
    // Draw the fuel bar
    fuelBar.render(window);
    displayScore(window, font, score, highScore);
    displayScreen(window, font, gameStarted, isPauseScreenVisible, isGameOver, isWinScreenVisible, level);
    displayHumansKilled(window, font, Humanoid::humansKilled);
    displayLevel(window, font, level);
    window.display();
}

// Function to display a text object
void Game::drawText(sf::RenderWindow &window, const sf::Text &text)
{
    window.draw(text);
}

// Function to display the score and high score
void Game::displayScore(sf::RenderWindow &window, sf::Font &font, int score, int highScore)
{
    sf::Text scoreText, highScoreText;
    scoreText.setFont(font);
    highScoreText.setFont(font);
    scoreText.setCharacterSize(24);
    highScoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    highScoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 20);
    highScoreText.setPosition(10, 40);
    scoreText.setString("Score: " + std::to_string(score));
    highScoreText.setString("Highscore: " + std::to_string(highScore));

    drawText(window, scoreText);
    drawText(window, highScoreText);
}

void Game::displayHumansKilled(sf::RenderWindow &window, sf::Font &font, int humansKilled)
{
    // Render Humans Killed counter
    sf::Text humansKilledText;
    humansKilledText.setFont(font);
    humansKilledText.setCharacterSize(24);
    humansKilledText.setFillColor(sf::Color::White);
    humansKilledText.setPosition(WINDOW_WIDTH - 200, 20);
    humansKilledText.setString("Humans Killed: " + std::to_string(Humanoid::humansKilled));

    drawText(window, humansKilledText); // Draw the humansKilledText
}

void Game::displayLevel(sf::RenderWindow &window, sf::Font &font, int level)
{
    // Render Humans Killed counter
    sf::Text humansKilledText;
    humansKilledText.setFont(font);
    humansKilledText.setCharacterSize(24);
    humansKilledText.setFillColor(sf::Color::White);
    humansKilledText.setPosition(WINDOW_WIDTH - 200, 60);
    humansKilledText.setString("Level: " + std::to_string(level));

    drawText(window, humansKilledText); // Draw the humansKilledText
}

// Function to display different screens
void Game::displayScreen(sf::RenderWindow &window, sf::Font &font, bool gameStarted, bool isPauseScreenVisible, bool isGameOver, bool isWinScreenVisible, int level)
{
    sf::Sprite screen;
    sf::Texture texture;

    if (!gameStarted && !isPauseScreenVisible && !isGameOver && !isWinScreenVisible)
    {
        // Display the splash screen
        if (!texture.loadFromFile("resources/splashScreen.jpeg"))
        {
            std::cerr << "Couldn't load splashScreen.jpeg" << std::endl;
            return;
        }
    }
    else if (isPauseScreenVisible)
    {
        // Display the pause screen
        if (!texture.loadFromFile("resources/pauseScreen.jpeg"))
        {
            std::cerr << "Couldn't load pauseScreen.jpeg" << std::endl;
            return;
        }
    }
    else if (isWinScreenVisible)
    {
        // Display the win screen
        if (!texture.loadFromFile("resources/levelScreen.jpeg"))
        {
            std::cerr << "Couldn't load levelScreen.jpeg" << std::endl;
            return;
        }
    }
    else if (isGameOver)
    {
        // Display the game over screen
        if (!texture.loadFromFile("resources/deathScreen.jpeg"))
        {
            std::cerr << "Couldn't load deathScreen.jpeg" << std::endl;
            return;
        }
    }

    screen.setTexture(texture);

    // Scale the screen to fit the window
    float scaleX = static_cast<float>(window.getSize().x) / texture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / texture.getSize().y;
    screen.setScale(scaleX, scaleY);

    window.draw(screen);
}

bool Game::gameOverStatus()
{
    return isGameOver;
}