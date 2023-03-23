
#include "DeadlyPlatform.h"
#include "AssetManager.h"

DeadlyPlatform::DeadlyPlatform(sf::Vector2f startingPos)
	: Platform(startingPos)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/DeadlyPlatform.png"));
}

void DeadlyPlatform::HandleCollision(SpriteObject& _other)
{
	_other.SetAlive(false);
}
