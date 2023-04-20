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
	, camera()
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
	// Update the camera based on render target size and player position
	camera = target.getDefaultView();
	camera.setCenter(player.GetPosition());

	// Update the render target to use the camera
	target.setView(camera);


	for (int i = 0; i < platforms.size(); ++i)
	{
		platforms[i]->Draw(target);
	}
	testDoor.Draw(target);
	player.Draw(target);

	// For any UI, reset the camera before drawing!
	target.setView(target.getDefaultView());

	// If there was UI, draw it now.
}
