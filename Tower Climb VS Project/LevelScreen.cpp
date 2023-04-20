
// Local includes
#include "LevelScreen.h"
#include "AssetManager.h"
#include "Game.h"
#include "Platform.h"
#include "MovingPlatform.h"
#include "BreakingPlatform.h"
#include "DeadlyPlatform.h"

// Library includes
#include <iostream>
#include <fstream>

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player()
	, platforms()
	, door()
	, camera()
	, currentLevel(0)
{
	LoadNextLevel();
}

void LevelScreen::Update(sf::Time frameTime)
{
	player.Update(frameTime);
	door.Update(frameTime);

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

	if (player.CheckCollision(door))
	{
		player.HandleCollision(door);
		door.HandleCollision(player);
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
	door.Draw(target);
	player.Draw(target);

	// For any UI, reset the camera before drawing!
	target.setView(target.getDefaultView());

	// If there was UI, draw it now.
}

void LevelScreen::LoadNextLevel()
{
	LoadLevel(currentLevel + 1);
}

void LevelScreen::LoadLevel(int levelNumber)
{
	// Load the level
	std::string fileName = "Assets/Levels/Level" + std::to_string(levelNumber) + ".txt";
	bool loaded = LoadLevel(fileName);

	// Set the current level
	if (loaded)
		currentLevel = levelNumber;
	else
	{
		// TODO: Show vitory screen!
	}
}

bool LevelScreen::LoadLevel(std::string fileName)
{

	// Open the level file
	std::ifstream inFile;
	inFile.open(fileName);


	// Make sure the file was opened
	if (!inFile)
	{
		return false;
		// Assume we finished all levels, we'll win now!
	}

	// Remove any existing platforms
	for (int i = 0; i < platforms.size(); ++i)
	{
		delete platforms[i];
		platforms[i] = nullptr;
	}
	platforms.clear();

	// Set the starting x and y coordinates used to position level objects
	float x = 0.0f;
	float y = 0.0f;

	// Define the spacing we will use for our grid
	const float X_SPACE = 150.0f;
	const float Y_SPACE = 150.0f;

	// Read each character one by one from the file...
	char ch;
	// Each time, try to read the next character
	// If successful, execute body of loop
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
		else if (ch == 'N') // Normal platform
		{
			platforms.push_back(new Platform(sf::Vector2f(x,y)));
		}
		else if (ch == 'B') // Breakable Platform
		{
			platforms.push_back(new BreakingPlatform(sf::Vector2f(x, y)));
		}
		else if (ch == 'D') // Deadly Platform
		{
			platforms.push_back(new DeadlyPlatform(sf::Vector2f(x, y)));
		}
		else if (ch == 'M') // Moving Platform
		{
			platforms.push_back(new MovingPlatform(sf::Vector2f(x, y), 0, gamePointer->GetRenderWindow().getSize().x));
		}
		else if (ch == 'O') // Door
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

	return true;
}
