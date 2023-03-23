#include "BreakingPlatform.h"
#include "AssetManager.h"

BreakingPlatform::BreakingPlatform()
	: Platform()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/BreakingPlatform.png"));
}

void BreakingPlatform::HandleCollision(SpriteObject _other)
{
	alive = false;
	solid = false;
}
