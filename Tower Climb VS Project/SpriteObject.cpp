#include "SpriteObject.h"
#include "VectorHelper.h"

SpriteObject::SpriteObject()
	: sprite()
	, collisionOffset(0,0)
	, collisionScale(1,1)
	, collisionType(CollisionType::AABB)
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
		switch (collisionType)
		{
			case CollisionType::CIRCLE:
			{
				sf::CircleShape circleCollision;
				float radius = GetBoundingCircleRadius();
				circleCollision.setPosition(GetCollisionCentre());
				circleCollision.setRadius(GetBoundingCircleRadius());
				circleCollision.setOrigin(radius, radius);
				sf::Color collisionColour = sf::Color::Green;
				if (colliding)
					collisionColour = sf::Color::Red;
				collisionColour.a = 100;
				circleCollision.setFillColor(collisionColour);
				target.draw(circleCollision);
				break;
			}
			case CollisionType::AABB:
			{
				sf::RectangleShape rectCollision;
				rectCollision.setPosition(GetCollisionCentre() - GetBoundingRectSize() / 2.0f);
				rectCollision.setSize(GetBoundingRectSize());
				sf::Color collisionColour = sf::Color::Green;
				if (colliding)
					collisionColour = sf::Color::Red;
				collisionColour.a = 100;
				rectCollision.setFillColor(collisionColour);
				target.draw(rectCollision);
				break;
			}
				break;
			default:
				break;
		}
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

sf::Vector2f SpriteObject::GetCollisionCentre()
{
	float width = sprite.getGlobalBounds().height;
	float height = sprite.getGlobalBounds().width;
	sf::Vector2f centre = position;
	centre.x += width / 2.0f;
	centre.y += height / 2.0f;
	centre += collisionOffset;
	return centre;
}

float SpriteObject::GetBoundingCircleRadius()
{
	float width = sprite.getGlobalBounds().height;
	width *= collisionScale.x;
	float height = sprite.getGlobalBounds().width;
	height *= collisionScale.y;
	float radius = width / 2.0f;
	if (height > width)
		radius = height / 2.0f;
	return radius;
}

sf::Vector2f SpriteObject::GetBoundingRectSize()
{
	float width = sprite.getGlobalBounds().height;
	width *= collisionScale.x;
	float height = sprite.getGlobalBounds().width;
	height *= collisionScale.y;
	return sf::Vector2f(width,height);
}

sf::FloatRect SpriteObject::GetAABB()
{
	sf::Vector2f topLeft = GetCollisionCentre() - GetBoundingRectSize() / 2.0f;
	sf::FloatRect rect = sf::FloatRect(topLeft, GetBoundingRectSize());
	return sf::FloatRect(rect);
}

bool SpriteObject::CheckCollision(SpriteObject _otherObject)
{
	sf::Vector2f otherCentre = _otherObject.GetCollisionCentre();
	float otherRadius = _otherObject.GetBoundingCircleRadius();

	sf::Vector2f distanceVector = otherCentre - GetCollisionCentre();

	float distanceSquare = VectorHelper::SquareMagnitude(distanceVector);

	float minDistance = otherRadius + GetBoundingCircleRadius();
	float minDistanceSquare = minDistance * minDistance;

	return distanceSquare <= minDistanceSquare;
}

void SpriteObject::SetColliding(bool _colliding)
{
	colliding = _colliding;
}
