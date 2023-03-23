#include "LevelScreen.h"
#include "AssetManager.h"
#include "Game.h"

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player()
	, testPlatform()
	, testMovingPlatform(0,newGamePointer->GetRenderWindow().getSize().x)
	, testBreakingPlatform()
	, testDeadlyPlatform()
	, testDoor()
{
	testPlatform.SetPosition(500.0f, 500.0f);
	testMovingPlatform.SetPosition(700.0f, 700.0f);
	testBreakingPlatform.SetPosition(100.0f, 600.0f);
	testDeadlyPlatform.SetPosition(600.0f, 600.0f);
	testDoor.SetPosition(500.0f, 350.0f);
	player.SetPosition(500.0f, 350.0f);
}

void LevelScreen::Update(sf::Time frameTime)
{
	player.Update(frameTime);
	testDoor.Update(frameTime);
	testPlatform.Update(frameTime);
	testMovingPlatform.Update(frameTime);
	testBreakingPlatform.Update(frameTime);
	testDeadlyPlatform.Update(frameTime);

	// Check collision between player and objects
	// First assume no collisions
	if (player.CheckCollision(testPlatform))
	{
		player.HandleCollision(testPlatform);
		testPlatform.HandleCollision(player);
	}
	if (player.CheckCollision(testMovingPlatform))
	{
		player.HandleCollision(testMovingPlatform);
		testMovingPlatform.HandleCollision(player);
	}
	if (player.CheckCollision(testBreakingPlatform))
	{
		player.HandleCollision(testBreakingPlatform);
		testBreakingPlatform.HandleCollision(player);
	}
	if (player.CheckCollision(testDeadlyPlatform))
	{
		player.HandleCollision(testDeadlyPlatform);
		testDeadlyPlatform.HandleCollision(player);
	}
	if (player.CheckCollision(testDoor))
	{
		player.HandleCollision(testDoor);
		testDoor.HandleCollision(player);
	}
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	testPlatform.Draw(target);
	testMovingPlatform.Draw(target);
	testBreakingPlatform.Draw(target);
	testDeadlyPlatform.Draw(target);
	testDoor.Draw(target);
	player.Draw(target);
}
