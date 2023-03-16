#pragma once
#include <SFML/Graphics.hpp>

enum class CollisionType
{
	CIRCLE,
	AABB
};

class SpriteObject
{
public:

	SpriteObject();

	virtual void Update(sf::Time frameTime);
	virtual void Draw(sf::RenderTarget& target);

	void SetPosition(float posX, float posY);
	void SetPosition(sf::Vector2f _position);
	sf::Vector2f GetPosition();

	bool CheckCollision(SpriteObject _otherObject);
	sf::Vector2f GetCollisionDepth(SpriteObject _otherObject);

	void SetColliding(bool _colliding);

private:

	sf::Vector2f GetCollisionCentre();
	float GetBoundingCircleRadius();
	sf::Vector2f GetBoundingRectSize();
	sf::FloatRect GetAABB();
	CollisionType GetCollisionType();

protected:

	sf::Sprite sprite;

	// Collision settings
	sf::Vector2f collisionOffset;
	sf::Vector2f collisionScale;

	CollisionType collisionType;

private:
	sf::Vector2f position;
	bool colliding;




};

