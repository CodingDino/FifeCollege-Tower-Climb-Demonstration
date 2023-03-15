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

	sf::Vector2f GetCollisionCentre();
	float GetBoundingCircleRadius();



	bool CheckCollision(SpriteObject _otherObject);

	void SetColliding(bool _colliding);


protected:

	sf::Sprite sprite;

	// Collision settings
	sf::Vector2f collisionOffset;
	sf::Vector2f collisionScale;

private:
	sf::Vector2f position;
	bool colliding;


};

