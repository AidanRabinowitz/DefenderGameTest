#include "game.h"
#include <iostream>
Game::Game()
    : score(0), highScore(0), gameStarted(false),
      quitConfirmation(false), isSplashScreenVisible(true),
      isPauseScreenVisible(false), isWinScreenVisible(false), isGameOver(false),
      level(1), previousLevelScore(0), fuelBar(200.0f, 20.0f, 100.f) //, isGamePaused(false)
{
    // Load background texture
    backgroundTexture.loadFromFile("resources/background.jpg");
    // Set the background sprite
    backgroundSprite.setTexture(backgroundTexture);
    if (!font.loadFromFile("resources/sansation.ttf"))
    {
        std::cout << "Loading font error" << std::endl;
    }
    // Initialize textures
    landerTexture.loadFromFile("resources/landerShip.png");
    fuelsTexture.loadFromFile("resources/fuel.png");
    playerTexture.loadFromFile("resources/playerShip.png");
    srand(static_cast<unsigned>(time(0))); // Seed random number generator
}

void Game::run(sf::RenderWindow &window)
{
    handleInput(window);
    update();
    render(window);
}

void Game::resetGame()
{
    // Reset player position
    player.setPosition(WINDOW_WIDTH / 2 - 25, WINDOW_HEIGHT - 60);

    // Clear the list of landers and missiles
    landers.clear();
    missiles.clear();
    lasers.clear();
    fuelBar.reset();
    player.resetCurrentFuel();
    fuels.clear();
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
                laser.shape.setSize(sf::Vector2f(5, 20));
                laser.shape.setFillColor(sf::Color::Cyan);
                laser.shape.setPosition(player.getPosition().x + 22, player.getPosition().y);
                laser.velocity.x = (mousePosition.x > playerCenter.x) ? LASER_SPEED : -LASER_SPEED;

                laser.setFired(true);
                lasers.push_back(laser);
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x > 0)
    {
        player.move(-PLAYER_SPEED, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x < WINDOW_WIDTH - 50)
    {
        player.move(PLAYER_SPEED, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player.getPosition().y > 0)
    {
        player.move(0, -PLAYER_SPEED);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player.getPosition().y < WINDOW_HEIGHT - 50)
    {
        player.move(0, PLAYER_SPEED);
    }
}
void Game::spawnLanders()
{
    if (spawnTimer.getElapsedTime().asMilliseconds() > SPAWN_INTERVAL)
    {
        Lander newLander;
        float xPos = static_cast<float>(rand() % static_cast<int>(WINDOW_WIDTH - newLander.landerSprite.getGlobalBounds().width));
        newLander.landerSprite.setPosition(sf::Vector2f(xPos, -newLander.landerSprite.getGlobalBounds().height));
        newLander.landerSprite.setTexture(landerTexture);
        landers.push_back(newLander);
        spawnTimer.restart();
    }
}

void Game::update()
{
    if (gameStarted && !isPauseScreenVisible && !isGameOver)
    {
        spawnLanders(); // Call the spawnLanders function
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

            // Set the fuel's position to a random location along the X-axis
            float xPos = static_cast<float>(rand() % static_cast<int>(WINDOW_WIDTH - fuelCan.fuelsSprite.getGlobalBounds().width));
            fuelCan.fuelsSprite.setPosition(sf::Vector2f(xPos, WINDOW_HEIGHT - fuelCan.fuelsSprite.getGlobalBounds().height));
            fuelCan.fuelsSprite.setTexture(fuelsTexture);
            fuels.push_back(fuelCan);
            fuelSpawnTimer.restart();
        }
        for (auto it = fuels.begin(); it != fuels.end();)
        {
            if (it->checkCollisionWithPlayer(player))
            {
                // Collision with fuel detected, remove the fuel
                it = fuels.erase(it);
                // Reset player's current fuel to 100.0f
                player.resetCurrentFuel();
                // Reset the fuel bar
                fuelBar.reset();
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

        // Check for collision between lasers and landers
        for (size_t i = 0; i < lasers.size(); i++)
        {
            for (size_t j = 0; j < landers.size(); j++)
            {
                if (!landers[j].isDestroyed() && lasers[i].shape.getGlobalBounds().intersects(landers[j].getSprite().getGlobalBounds()))
                {
                    score += 10;
                    landers[j].destroy();
                    lasers.erase(lasers.begin() + i);
                    i--;   // Adjust the index after removal
                    break; // Exit the inner loop when a collision occurs
                }
            }
        }

        // Check for collision between player and landers
        for (size_t i = 0; i < landers.size(); i++)
        {
            if (!landers[i].isDestroyed() && player.getGlobalBounds().intersects(landers[i].landerSprite.getGlobalBounds()))
            {
                isGameOver = true;
                break;
            }
        }

        // Check for collision between player and missiles
        for (size_t i = 0; i < missiles.size(); i++)
        {
            if (missiles[i].shape.getGlobalBounds().intersects(player.getGlobalBounds()))
            {
                isGameOver = true;
                break;
            }
        }
    }
}

void Game::render(sf::RenderWindow &window) // Rendering the game shapes and sprites
{
    window.clear();
    window.draw(backgroundSprite);
    player.render(window);

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

// Function to display different screens
void Game::displayScreen(sf::RenderWindow &window, sf::Font &font, bool gameStarted, bool isPauseScreenVisible, bool isGameOver, bool isWinScreenVisible, int level)
{
    if (!gameStarted && !isPauseScreenVisible && !isGameOver && !isWinScreenVisible)
    {
        sf::Text leftColumnText;

        leftColumnText.setFont(font);
        leftColumnText.setCharacterSize(24);
        leftColumnText.setFillColor(sf::Color::White);
        leftColumnText.setPosition(100, 200); // Adjust the position as needed
        leftColumnText.setString("Press Space to Start\n"
                                 "\n"
                                 "\n"
                                 "WASD keys to move\n"
                                 "\n"
                                 "\n"
                                 "Left mouse click to fire");
        drawText(window, leftColumnText);

        sf::Text rightColumnText;

        rightColumnText.setFont(font);
        rightColumnText.setCharacterSize(24);
        rightColumnText.setFillColor(sf::Color::White);
        rightColumnText.setPosition(390, 200); // Adjust the position as needed
        rightColumnText.setString("Capture fuel to refill tank\n"
                                  "\n"
                                  "\n"
                                  "Hover mouse left to change direction\n"
                                  "\n"
                                  "\n"
                                  "esc to pause");
        drawText(window, rightColumnText);
    }

    if (isPauseScreenVisible)
    {
        sf::Text pauseText;
        pauseText.setFont(font);
        pauseText.setCharacterSize(32);
        pauseText.setFillColor(sf::Color::White);
        pauseText.setPosition(200, 200);
        pauseText.setString("Are you sure you want to quit?\nY for yes, N for no");

        drawText(window, pauseText);
    }

    if (isWinScreenVisible)
    {
        sf::Text winText;
        winText.setFont(font);
        winText.setCharacterSize(32);
        winText.setFillColor(sf::Color::White);
        winText.setPosition(200, 200);
        winText.setString("You killed 10 landers! YOU WIN!\nProceed to level " + std::to_string(level + 1) + "?\nY for yes, N for no");

        drawText(window, winText);
    }

    if (isGameOver)
    {
        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setCharacterSize(32);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setPosition(200, 200);
        gameOverText.setString("You Died\nPlay again?\nY for yes, N to close the window");

        drawText(window, gameOverText);
        resetGame();
    }
}