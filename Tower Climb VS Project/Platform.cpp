#include "Platform.h"
#include "AssetManager.h"

Platform::Platform()
	: SpriteObject()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Platform.png"));
}
