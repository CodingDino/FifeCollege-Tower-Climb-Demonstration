#include "LevelScreen.h"
#include "AssetManager.h"
#include "Platform.h"
#include "MovingPlatform.h"
#include "BreakingPlatform.h"
#include "DeadlyPlatform.h"
#include "Game.h"

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player()
	, testDoor(this)
	, endPanel(newGamePointer->GetWindow())
	, gameRunning(true)
	, platforms()
{
	Restart();
}

void LevelScreen::Update(sf::Time frameTime)
{
	if (gameRunning)
	{
		player.Update(frameTime);
		for (int i = 0; i < platforms.size(); ++i)
		{
			platforms[i]->Update(frameTime);
		}

		player.SetColliding(false);
		for (int i = 0; i < platforms.size(); ++i)
		{
			platforms[i]->SetColliding(false);
		}
		testDoor.SetColliding(false);

		for (int i = 0; i < platforms.size(); ++i)
		{
			if (platforms[i]->CheckCollision(player))
			{
				player.SetColliding(true);
				platforms[i]->SetColliding(true);
				player.HandleCollision(*platforms[i]);
				platforms[i]->HandleCollision(player);
			}
		}
		if (player.CheckCollision(testDoor))
		{
			player.SetColliding(true);
			testDoor.SetColliding(true);
			testDoor.HandleCollision(player);
		}
	}
	else
	{
		endPanel.Update(frameTime);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			Restart();
		}
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

	if (!gameRunning)
	{
		endPanel.Draw(target);
	}
}

void LevelScreen::TriggerEndState(bool _win)
{
	// TODO
	gameRunning = false;
	endPanel.StartAnimation();
}

void LevelScreen::Restart()
{

	player.SetPosition(500, 350);

	// clear out our platforms before making new ones
	// Make sure to delete BEFORE clearing!
	for (int i = 0; i < platforms.size(); ++i) 
	{
		delete platforms[i];
		platforms[i] = nullptr;
	}
	platforms.clear();

	platforms.push_back(new Platform(sf::Vector2f(500, 500)));
	platforms.push_back(new Platform(sf::Vector2f(900, 500)));
	platforms.push_back(new BreakingPlatform(sf::Vector2f(100, 500)));
	platforms.push_back(new DeadlyPlatform(sf::Vector2f(600, 900)));
	platforms.push_back(new MovingPlatform(sf::Vector2f(500, 700), sf::Vector2f(0, 700), sf::Vector2f(1000, 700)));


	testDoor.SetPosition(900, 350);

	gameRunning = true;


}
