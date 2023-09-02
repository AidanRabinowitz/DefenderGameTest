#include <SFML/Graphics.hpp>
#include "PlayerShip.h"
#include "PlayerLaser.h"
#include "EnemyLander.h"
#include "EnemyMissile.h"
#include <vector>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Defender");

	PlayerShip playerShip(sf::Vector2f(400.f, 550.f));

	std::vector<PlayerLaser> playerLasers;
	std::vector<sf::RectangleShape> enemyMissiles; // Update to use sf::RectangleShape

	std::vector<EnemyLander> enemyLanders;

	// Create and add EnemyLander objects to the enemyLanders vector
	enemyLanders.push_back(EnemyLander(sf::Vector2f(400.f, 100.f), 2.0f, enemyMissiles)); // Adjust fireRate as needed
	enemyLanders.push_back(EnemyLander(sf::Vector2f(500.f, 100.f), 2.0f, enemyMissiles)); // Adjust fireRate as needed
	// Add more as needed

	bool gameStarted = false;
	bool quitConfirmation = false; // To track if the quit confirmation dialog is shown

	sf::Font font;
	if (!font.loadFromFile("resources/sansation.ttf"))
	{
		return 1;
	}

	sf::Text startMessage;
	startMessage.setFont(font);
	startMessage.setCharacterSize(40);
	startMessage.setPosition(100.f, 250.f);
	startMessage.setFillColor(sf::Color::White);
	startMessage.setString("Press any key to start");

	sf::Text confirmText; // Text for the quit confirmation
	confirmText.setFont(font);
	confirmText.setCharacterSize(40);
	confirmText.setPosition(100.f, 250.f);
	confirmText.setFillColor(sf::Color::White);
	confirmText.setString("Are you sure you want to quit? (Y/N)");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			// Handle mouse click
			playerShip.handleMouseClick(event, playerLasers);

			if (!gameStarted && event.type == sf::Event::KeyPressed)
			{
				gameStarted = true;
			}
		}

		if (gameStarted && !quitConfirmation)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !quitConfirmation)
			{
				quitConfirmation = true; // Show the quit confirmation dialog
			}
			float deltaTime = 0.016f; // Adjust this as needed
			playerShip.update(deltaTime);

			// Update and draw enemy landers
			for (size_t i = 0; i < enemyLanders.size(); ++i)
			{
				enemyLanders[i].update(deltaTime, playerShip.getPosition(), enemyMissiles);
				enemyLanders[i].draw(window);
			}

			// ...

			// Update and draw enemy missiles
			for (size_t i = 0; i < enemyMissiles.size(); ++i)
			{
				// Update the position of the enemy missiles
				enemyMissiles[i].move(sf::Vector2f(1.f, 0.f)); // Adjust the movement as needed
				// Draw the enemy missiles
				window.draw(enemyMissiles[i]);
			}

			for (size_t i = 0; i < playerLasers.size(); ++i)
			{
				playerLasers[i].update(deltaTime);
				if (playerLasers[i].isOutOfBounds())
				{
					playerLasers.erase(playerLasers.begin() + i);
					--i;
				}
			}

			for (size_t i = 0; i < enemyLanders.size(); ++i)
			{
				enemyLanders[i].update(deltaTime, playerShip.getPosition(), enemyMissiles);
			}

			window.clear(sf::Color::Black);
			playerShip.draw(window);
			for (const PlayerLaser &laser : playerLasers)
			{
				laser.draw(window);
			}
			// Draw enemy landers
			for (const EnemyLander &lander : enemyLanders)
			{
				lander.draw(window);
			}
		}
		else if (quitConfirmation)
		{
			window.clear(sf::Color::Black);
			window.draw(confirmText);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
			{
				quitConfirmation = false; // Hide the confirmation dialog
				gameStarted = false;	  // Go back to the start screen
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
			{
				quitConfirmation = false; // Hide the confirmation dialog
			}
			!gameStarted; // Toggle the gameStarted state
		}
		else
		{

			window.clear(sf::Color::Black);
			window.draw(startMessage);
		}

		window.display();
	}

	return 0;
}
