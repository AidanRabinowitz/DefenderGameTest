#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "Game.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Defender-like Game");
	window.setFramerateLimit(60);

	Game game; // Create a Game object

	while (window.isOpen())
	{
		// Run the game loop using the Game class
		game.run(window);
	}

	return 0;
}
