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

	Game game;

	while (window.isOpen())
	{
		game.run(window);
	}

	return 0;
}
