#include "Door.h"
#include "AssetManager.h"

Door::Door()
	: SpriteObject()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Door.png"));
}
