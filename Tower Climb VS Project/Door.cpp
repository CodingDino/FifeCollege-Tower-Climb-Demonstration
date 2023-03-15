#include "Door.h"
#include "AssetManager.h"

Door::Door()
	: SpriteObject()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Door.png"));
	collisionType = CollisionType::AABB;
	collisionScale = sf::Vector2f(0.5f, 0.85f);
	collisionOffset = sf::Vector2f(0.0f, 10.0f);
}
