#include "game.h"

//sf::Sprite splashBackground;
//sf::Texture splashBackgroundTexture;

Game::Game()
    : score(0), highScore(0), gameStarted(false),
      quitConfirmation(false), isSplashScreenVisible(true),
      isPauseScreenVisible(false), isGameOver(false)
{
    // Initialize the player
    player.setSize(sf::Vector2f(50, 50));
    player.setFillColor(sf::Color::Green);
    player.setPosition(WINDOW_WIDTH / 2 - 25, WINDOW_HEIGHT - 60);

    // Load font and other resources here
    if (!font.loadFromFile("resources/sansation.ttf"))
    {
        // Handle font loading error
    }

   // if (!splashBackgroundTexture.loadFromFile("resources/background.png"))
    //{
        // Handle the error if the image fails to load
    //}

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

    // Handle input for starting the game
    if (!gameStarted && !isPauseScreenVisible && !isGameOver)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {
            gameStarted = true;
            isSplashScreenVisible = false;
            score = 0; // Reset the score when the game starts
        }
    }
    // Handle input for pausing the game
    else if (gameStarted && !isPauseScreenVisible && !isGameOver)
    {
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
                laser.velocity.x = LASER_SPEED;
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

        // Player movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x > 0)
            player.move(-PLAYER_SPEED, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x < WINDOW_WIDTH - 50)
            player.move(PLAYER_SPEED, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player.getPosition().y > 0)
            player.move(0, -PLAYER_SPEED);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player.getPosition().y < WINDOW_HEIGHT - 50)
            player.move(0, PLAYER_SPEED);

        // Spawn Landers
        if (spawnTimer.getElapsedTime().asMilliseconds() > SPAWN_INTERVAL)
        {
            // Randomly generate a position for the lander, away from the player
            sf::Vector2f landerSpawnPosition(rand() % (WINDOW_WIDTH - 30), -30); // Adjust as needed
            landers.push_back(Lander(player.getPosition()));
            landers.back().shape.setPosition(landerSpawnPosition);
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
                landers[i].shape.move(0, LANDER_SPEED); // Move downward
            }

            // Remove Landers that go out of bounds
            if (landers[i].shape.getPosition().y > WINDOW_HEIGHT)
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
                if (!landers[j].isDestroyed() && lasers[i].shape.getGlobalBounds().intersects(landers[j].shape.getGlobalBounds()))
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
            if (!landers[i].isDestroyed() && player.getGlobalBounds().intersects(landers[i].shape.getGlobalBounds()))
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
   // window.draw(splashBackground);
    window.draw(player);

    // Draw Landers
    for (const auto &lander : landers)
    {
        if (!lander.isDestroyed())
        {
            window.draw(lander.shape);
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
    if (!gameStarted && !isPauseScreenVisible && !isGameOver)
    {
        sf::Text splashText;
        splashText.setFont(font);
        splashText.setCharacterSize(30);
        splashText.setFillColor(sf::Color::White);
        splashText.setPosition(200, 400);
        splashText.setString(" Instructions:\n- Use A/D/W/S to move\n- Left-click to shoot\n- Press Space to start");


        sf::Text highScoreText;
        highScoreText.setFont(font);
        highScoreText.setCharacterSize(24);
        highScoreText.setFillColor(sf::Color::White);
        highScoreText.setPosition(200, 300);
        highScoreText.setString("Highscore: " + std::to_string(highScore));

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