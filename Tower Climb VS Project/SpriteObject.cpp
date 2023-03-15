#include "SpriteObject.h"
#include "VectorHelper.h"

SpriteObject::SpriteObject()
	: sprite()
	, position(0,0)
	, colliding(false)
{
}

void SpriteObject::Update(sf::Time frameTime)
{
}

void SpriteObject::Draw(sf::RenderTarget& target)
{
	target.draw(sprite);

	bool drawCollision = true;

	if (drawCollision)
	{
		sf::CircleShape circleCollision;
		float radius = GetBoundingCircleRadius();
		circleCollision.setPosition(GetBoundingCircleCentre());
		circleCollision.setRadius(GetBoundingCircleRadius());
		circleCollision.setOrigin(radius, radius);
		sf::Color collisionColour = sf::Color::Green;
		if (colliding)
			collisionColour = sf::Color::Red;
		collisionColour.a = 100;
		circleCollision.setFillColor(collisionColour);
		target.draw(circleCollision);
	}
}

void SpriteObject::SetPosition(float posX, float posY)
{
	SetPosition(sf::Vector2f(posX, posY));
}

void SpriteObject::SetPosition(sf::Vector2f _position)
{
	position = _position;
	sprite.setPosition(position);
}

sf::Vector2f SpriteObject::GetPosition()
{
	return position;
}

sf::Vector2f SpriteObject::GetBoundingCircleCentre()
{
	float width = sprite.getGlobalBounds().height;
	float height = sprite.getGlobalBounds().width;
	sf::Vector2f centre = position;
	centre.x += width / 2.0f;
	centre.y += height / 2.0f;
	return centre;
}

float SpriteObject::GetBoundingCircleRadius()
{
	float width = sprite.getGlobalBounds().height;
	float height = sprite.getGlobalBounds().width;
	float radius = width / 2.0f;
	if (height > width)
		radius = height / 2.0f;
	return radius;
}

bool SpriteObject::CheckCollision(SpriteObject _otherObject)
{
	sf::Vector2f otherCentre = _otherObject.GetBoundingCircleCentre();
	float otherRadius = _otherObject.GetBoundingCircleRadius();

	sf::Vector2f distanceVector = otherCentre - GetBoundingCircleCentre();

	float distanceSquare = VectorHelper::SquareMagnitude(distanceVector);

	float minDistance = otherRadius + GetBoundingCircleRadius();
	float minDistanceSquare = minDistance * minDistance;

	return distanceSquare <= minDistanceSquare;
}

void SpriteObject::SetColliding(bool _colliding)
{
	colliding = _colliding;
}
