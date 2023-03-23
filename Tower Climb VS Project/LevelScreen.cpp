#include "LevelScreen.h"
#include "AssetManager.h"
#include "Game.h"
#include "Platform.h"
#include "MovingPlatform.h"
#include "BreakingPlatform.h"
#include "DeadlyPlatform.h"

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player()
	, platforms()
	, testDoor()
{
	platforms.push_back(new Platform(sf::Vector2f(500.0f, 500.0f)));
	platforms.push_back(new MovingPlatform(sf::Vector2f(900.0f, 800.0f), 0, gamePointer->GetRenderWindow().getSize().x));
	platforms.push_back(new BreakingPlatform(sf::Vector2f(100.0f, 600.0f)));
	platforms.push_back(new DeadlyPlatform(sf::Vector2f(700.0f, 600.0f)));

	testDoor.SetPosition(500.0f, 350.0f);
	player.SetPosition(500.0f, 350.0f);
}

void LevelScreen::Update(sf::Time frameTime)
{
	player.Update(frameTime);
	testDoor.Update(frameTime);

	for (int i = 0; i < platforms.size(); ++i)
	{
		platforms[i]->Update(frameTime);
	}

	// Check collision between player and objects

	for (int i = 0; i < platforms.size(); ++i)
	{
		if (player.CheckCollision(*platforms[i]))
		{
			player.HandleCollision(*platforms[i]);
			platforms[i]->HandleCollision(player);
		}
	}

	if (player.CheckCollision(testDoor))
	{
		player.HandleCollision(testDoor);
		testDoor.HandleCollision(player);
	}
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	for (int i = 0; i < platforms.size(); ++i)
	{
		platforms[i]->Draw(target);
	}
	testDoor.Draw(target);
	player.Draw(target);
}
