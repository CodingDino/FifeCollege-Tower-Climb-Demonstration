#include "LevelScreen.h"
#include "AssetManager.h"

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player()
	, testPlatform()
	, testDoor()
{
	testPlatform.SetPosition(500.0f, 500.0f);
	testDoor.SetPosition(500.0f, 350.0f);
	player.SetPosition(500.0f, 350.0f);
}

void LevelScreen::Update(sf::Time frameTime)
{
	player.Update(frameTime);

	// Check collision between player and objects
	// First assume no collisions
	player.SetColliding(false);
	testPlatform.SetColliding(false);
	testDoor.SetColliding(false);
	if (player.CheckCollision(testPlatform))
	{
		player.SetColliding(true);
		testPlatform.SetColliding(true);
		player.HandleSolidCollision(testPlatform);
	}
	if (player.CheckCollision(testDoor))
	{
		player.SetColliding(true);
		testDoor.SetColliding(true);
	}
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	testPlatform.Draw(target);
	testDoor.Draw(target);
	player.Draw(target);
}
