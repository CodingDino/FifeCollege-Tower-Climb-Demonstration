#include "LevelScreen.h"
#include "AssetManager.h"

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player()
	, testPlatform()
	, testDoor()
{

	player.SetPosition(500, 350);
	testPlatform.SetPosition(500, 500);
	testDoor.SetPosition(500, 350);

}

void LevelScreen::Update(sf::Time frameTime)
{
	player.Update(frameTime);

	player.SetColliding(false);
	testPlatform.SetColliding(false);
	testDoor.SetColliding(false);

	if (testPlatform.CheckCollision(player))
	{
		player.SetColliding(true);
		testPlatform.SetColliding(true);
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
