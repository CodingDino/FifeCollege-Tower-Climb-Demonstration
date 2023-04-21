// Project includes
#include "LevelScreen.h"
#include "AssetManager.h"
#include "Platform.h"
#include "MovingPlatform.h"
#include "BreakingPlatform.h"
#include "DeadlyPlatform.h"
#include "Game.h"

// Library includes
#include <iostream>
#include <fstream>

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player()
	, door(this)
	, endPanel(newGamePointer->GetWindow())
	, gameRunning(true)
	, platforms()
	, camera()
	, currentLevel(1)
{
	LoadLevel(1);
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
		door.SetColliding(false);

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
		if (player.CheckCollision(door))
		{
			player.SetColliding(true);
			door.SetColliding(true);
			door.HandleCollision(player);
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
	// Update the camera based on the render target size
	// and player position
	camera = target.getDefaultView();
	sf::Vector2f cameraCentre = camera.getCenter();
	cameraCentre.y = player.GetPosition().y;
	camera.setCenter(cameraCentre);

	// Update the render target to use the camera
	target.setView(camera);

	// Draw "world" objects (ones that should use the camera)
	for (int i = 0; i < platforms.size(); ++i)
	{
		platforms[i]->Draw(target);
	}
	door.Draw(target);
	player.Draw(target);

	// For any UI, reset the camera to the default view
	// before drawing
	target.setView(target.getDefaultView());

	// Draw UI objects (use the base view)
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

bool LevelScreen::LoadNextLevel()
{
	return LoadLevel(currentLevel + 1);
}

void LevelScreen::Restart()
{
	LoadLevel(currentLevel);
}

bool LevelScreen::LoadLevel(int levelNumber)
{
	// Construct level name from number
	std::string levelName = "Level" + std::to_string(levelNumber);

	bool success = LoadLevel(levelName);

	if (success)
	{
		currentLevel = levelNumber;
	}

	return success;
}

bool LevelScreen::LoadLevel(std::string fileName)
{
	// Open the level file
	std::ifstream inFile;
	std::string filePath = "Assets/Levels/" + fileName + ".txt";
	inFile.open(filePath);
	
	// Make sure the file was actually opened
	if (!inFile)
	{
		// File was not opened
		return false;
	}

	// clear out our platforms before making new ones
	// Make sure to delete BEFORE clearing!
	for (int i = 0; i < platforms.size(); ++i)
	{
		delete platforms[i];
		platforms[i] = nullptr;
	}
	platforms.clear();

	// Set the starting x and y coordinates used to position
	// our level objects
	float x = 0.0f;
	float y = 0.0f;

	// Define the spacing we will use for our grid
	const float X_SPACE = 150.0f;
	const float Y_SPACE = 150.0f;

	// Read each character one by one from the file...
	char ch;
	// Each time, try to read the next character
	// If successful, execute the body of loop
	// the "noskipws" means our input from the file will include
	// the white space (spaces and new lines)
	while (inFile >> std::noskipws >> ch)
	{
		// Perform actions based on what character was read in

		if (ch == ' ')
		{
			x += X_SPACE;
		}
		else if (ch == '\n')
		{
			y += Y_SPACE;
			x = 0;
		}
		else if (ch == 'P')
		{
			player.SetPosition(x, y);
		}
		else if (ch == 'N')
		{
			platforms.push_back(new Platform(sf::Vector2f(x, y)));
		}
		else if (ch == 'B')
		{
			platforms.push_back(new BreakingPlatform(sf::Vector2f(x, y)));
		}
		else if (ch == 'D')
		{
			platforms.push_back(new DeadlyPlatform(sf::Vector2f(x, y)));
		}
		else if (ch == 'M')
		{
			platforms.push_back(new MovingPlatform(sf::Vector2f(x, y), sf::Vector2f(0, y), sf::Vector2f(gamePointer->GetWindow()->getSize().x, y)));
		}
		else if (ch == 'O')
		{
			door.SetPosition(x, y);
		}
		else if (ch == '-')
		{
			// Do nothing - empty space
		}
		else
		{
			std::cerr << "Unrecognised character in level file: " << ch;
		}

	}

	// Close the file now that we are done with it
	inFile.close();

	// Set our game to start
	gameRunning = true;

	// return true because we succesfully loaded the file.
	return true;
}
