#include "game.h"
// #include "Player.h"
Game::Game()
    : score(0), highScore(0), gameStarted(false),
      quitConfirmation(false), isSplashScreenVisible(true),
      isPauseScreenVisible(false), isWinScreenVisible(false), isGameOver(false), level(1), previousLevelScore(0) //, isGamePaused(false)
{
    // Load background texture
    backgroundTexture.loadFromFile("resources/background.jpg");

    // Set the background sprite
    backgroundSprite.setTexture(backgroundTexture);
    if (!font.loadFromFile("resources/sansation.ttf"))
    {
        // Handle font loading error
    }
    // Initialize landers
    for (int i = 0; i < MAX_LANDERS; ++i)
    {
        Lander newLander;
        // Set the position or other properties of newLander as needed
        landers.push_back(newLander);
    }
    playerTexture.loadFromFile("resources/playerShip.png");
    player.setTexture(playerTexture);
    player.scale(sf::Vector2f(0.1, 0.1));
    player.setPosition(WINDOW_WIDTH / 2 - 25, WINDOW_HEIGHT - 60);
    // Player player();
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
    // Reset any other game-related variables if needed
}

void Game::handleInput(sf::RenderWindow &window)
{
    sf::Event event;
    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    sf::Vector2f playerCenter = player.getPosition() + sf::Vector2f(player.getGlobalBounds().width / 2, player.getGlobalBounds().height / 2);

    if (mousePosition.x > playerCenter.x)
    {
        // Mouse is to the right of the player
        player.setScale(0.1f, 0.1f); // Set scale normally
        // Fire laser to the right
        // Add your code for firing the laser to the right
    }
    else
    {
        // Mouse is to the left of the player
        player.setScale(-0.1f, 0.1f); // Flip horizontally by setting X scale to negative
        // Fire laser to the left
        // Add your code for firing the laser to the left
    }
    // Handle input for starting the game
    if (!gameStarted && !isPauseScreenVisible && !isGameOver && !isWinScreenVisible)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {
            gameStarted = true;
            isSplashScreenVisible = false;
            score = 0; // Reset the score when the game starts
        }
    }
    // Handle input for pausing the game
    else if (gameStarted && !isPauseScreenVisible && !isGameOver && !isWinScreenVisible)
    {
        // Check if the player has won
        int oldScore = score;
        if (score >= previousLevelScore + 100)
        {
            isWinScreenVisible = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            isPauseScreenVisible = true;
        }
    }
    // Handle input for quit confirmation screen
    else if (isPauseScreenVisible)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y))
        {
            isPauseScreenVisible = false;
            gameStarted = false;
            if (score > highScore)
            {
                highScore = score;
            }
            score = 0; // Reset the score
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y))
        {
            isWinScreenVisible = false;
            gameStarted = true;

            // Increment the level
            level++;
            // Update the previousLevelScore for the next level
            previousLevelScore = score;
            gameStarted = true;
            // Continue the game without resetting the score
            // You can add logic to reset other game elements for the new level if needed
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N))
        {
            // Start a new game
            isWinScreenVisible = false;
            // gameStarted = false;
            isSplashScreenVisible = true;
            resetGame();
            // Reset the score if the player chooses to start a new game
            score = 0;
            // Reset the previousLevelScore for a new game
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
            score = 0; // Reset the score
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

    // Game-specific input handling
    // ...

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

    // Player movement
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

void Game::update()
{
    // Update game logic here

    if (gameStarted && !isPauseScreenVisible && !isGameOver)
    {
        // Game-specific update logic

        // Spawn Landers
        if (spawnTimer.getElapsedTime().asMilliseconds() > SPAWN_INTERVAL)
        {
            // Create a new lander
            Lander newLander;

            // Set the lander's position to a random location along the X-axis
            float xPos = static_cast<float>(rand() % static_cast<int>(WINDOW_WIDTH - newLander.getSprite().getGlobalBounds().width));
            newLander.getSprite().setPosition(sf::Vector2f(xPos, -newLander.getSprite().getGlobalBounds().height));

            // Add the new lander to the list
            landers.push_back(newLander);

            spawnTimer.restart();
        }
        // Fire Missiles from Landers towards the player's ship
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

        for (size_t i = 0; i < landers.size(); i++)
        {
            if (!landers[i].isDestroyed())
            {
                landers[i].landerSprite.move(0, LANDER_SPEED); // Move downward
            }

            // Remove Landers that go out of bounds
            if (landers[i].landerSprite.getPosition().y > WINDOW_HEIGHT)
            {
                landers.erase(landers.begin() + i);
                i--;
                missiles.erase(missiles.begin() + i);
                i--;
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
                    // Laser hit a lander
                    score += 10;          // Increment the score (adjust as needed)
                    landers[j].destroy(); // Mark the lander as destroyed
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

void Game::render(sf::RenderWindow &window)
{
    // Render game elements here
    window.clear();
    window.draw(backgroundSprite);

    window.draw(player);

    // Draw Landers
    for (auto &lander : landers)
    {
        if (!lander.isDestroyed())
        {
            window.draw(lander.landerSprite);
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

    // Display and update the score
    // Create a text object for the current score
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);
    scoreText.setString("Score: " + std::to_string(score)); // Display the score

    // Create a text object for the high score
    sf::Text highScoreText;
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(24);
    highScoreText.setFillColor(sf::Color::White);
    highScoreText.setPosition(10, 40); // Adjust the vertical position for the high score
    highScoreText.setString("Highscore: " + std::to_string(highScore));

    window.draw(scoreText);
    window.draw(highScoreText);

    // Display the splash screen
    if (!gameStarted && !isPauseScreenVisible && !isGameOver && !isWinScreenVisible)
    {
        sf::Text splashText;
        splashText.setFont(font);
        splashText.setCharacterSize(32);
        splashText.setFillColor(sf::Color::White);
        splashText.setPosition(200, 200);
        splashText.setString("Press Space to Start \n "
                             " \n WASD keys to move \n "
                             " \n Left mouseclick to fire  \n "
                             " \n Hover mouse left or right of \n "
                             " \n player to change direction \n "
                             " \n esc to pause");

        window.draw(splashText);
        window.draw(highScoreText);
    }

    // Display the pause screen
    if (isPauseScreenVisible)
    {
        sf::Text pauseText;
        pauseText.setFont(font);
        pauseText.setCharacterSize(32);
        pauseText.setFillColor(sf::Color::White);
        pauseText.setPosition(200, 200);
        pauseText.setString("Are you sure you want to quit?\nY for yes, N for no");

        window.draw(pauseText);
    }
    if (isWinScreenVisible)
    {
        sf::Text winText;
        winText.setFont(font);
        winText.setCharacterSize(32);
        winText.setFillColor(sf::Color::White);
        winText.setPosition(200, 200);
        winText.setString("You killed 10 landers! YOU WIN!\nProceed to level " + std::to_string(level + 1) + "?\nY for yes, N for no");

        window.draw(winText);
    }

    // Display the game over screen
    if (isGameOver)
    {
        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setCharacterSize(32);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setPosition(200, 200);
        gameOverText.setString("You Died\nPlay again?\nY for yes, N for no");

        window.draw(gameOverText);
        resetGame();
    }

    // Display everything on the window
    window.display();
}