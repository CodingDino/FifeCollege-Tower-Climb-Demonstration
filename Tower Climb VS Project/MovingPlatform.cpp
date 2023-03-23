#include "MovingPlatform.h"
#include "AssetManager.h"

MovingPlatform::MovingPlatform(sf::Vector2f startingPos, float newMinX, float newMaxX)
	: Platform(startingPos)
	, SPEED(100)
	, MIN_X(newMinX)
	, MAX_X(newMaxX)
	, horizontalVel(SPEED)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/MovingPlatform.png"));
}

void MovingPlatform::Update(sf::Time frameTime)
{
	float frameSeconds = frameTime.asSeconds();

	sf::Vector2f newPos = GetPosition();
	newPos.x += horizontalVel * frameSeconds;

	// Check if we hit the edges and if so, turn around
	if (newPos.x + sprite.getGlobalBounds().width >= MAX_X)
	{
		newPos.x = MAX_X - sprite.getGlobalBounds().width;
		horizontalVel *= -1.0f;
	}
	else if (newPos.x <= MIN_X)
	{
		newPos.x = MIN_X;
		horizontalVel *= -1.0f;
	}

	SetPosition(newPos);
	SpriteObject::Update(frameTime);
}
