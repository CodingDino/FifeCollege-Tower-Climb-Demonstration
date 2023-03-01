#include "Game.h"

Game::Game()
	: window(sf::VideoMode::getDesktopMode(), "Tower Climb", sf::Style::Titlebar | sf::Style::Close)
	, gameClock()
{
	// Window setup
	window.setMouseCursorVisible(false);

	// TODO: Setup screens
}

void Game::RunGameLoop()
{
	// Repeat as long as the window is open
	while (window.isOpen())
	{
		Update();
		Draw();
		EventHandling();
	}

}

void Game::EventHandling()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		// Close the game if escape is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
	}
}

void Game::Update()
{
	sf::Time frameTime = gameClock.restart();

	// TODO: Update current screen

	// TODO: Handle changes to other screens

}

void Game::Draw()
{
	window.clear();
	
	// TODO: Draw current screen

	window.display();
}
