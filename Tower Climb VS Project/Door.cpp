#include "Door.h"
#include "AssetManager.h"
#include "LevelScreen.h"

Door::Door(LevelScreen* newLevelScreen)
	: SpriteObject()
	, levelScreen(newLevelScreen)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Door.png"));
	collisionOffset = sf::Vector2f(0, 20.0f);
	collisionScale = sf::Vector2f(0.45, 1.0f);
}

void Door::HandleCollision(SpriteObject& other)
{
	bool loaded = levelScreen->LoadNextLevel();

	if (loaded == false)
	{
		levelScreen->TriggerEndState(true);
	}

	SpriteObject::HandleCollision(other);
}
