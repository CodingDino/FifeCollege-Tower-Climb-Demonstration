
#include "DeadlyPlatform.h"
#include "AssetManager.h"

DeadlyPlatform::DeadlyPlatform()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/DeadlyPlatform.png"));
}

void DeadlyPlatform::HandleCollision(SpriteObject& _other)
{
	_other.SetAlive(false);
}
