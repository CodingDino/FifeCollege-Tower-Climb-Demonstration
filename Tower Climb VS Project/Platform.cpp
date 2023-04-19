#include "Platform.h"
#include "AssetManager.h"

Platform::Platform(sf::Vector2f newPosition)
	: SpriteObject()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Platform.png"));
	collisionOffset = sf::Vector2f(0, -57.0f);
	collisionScale = sf::Vector2f(1.0f, 0.25f);
	SetPosition(newPosition);
}
