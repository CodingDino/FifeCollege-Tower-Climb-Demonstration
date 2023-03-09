#include "Player.h"
#include "AssetManager.h"


enum class PhysicsType {
	FORWARD_EULER,
	BACKWARD_EULER
};


Player::Player()
	: SpriteObject()
	, position(100,300)
	, velocity(0,0)
	, acceleration(0,0)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/PlayerStand.png"));
	sprite.setPosition(position);
}

void Player::Update(sf::Time frameTime)
{
	const float DRAG_MULT = 0.99f;
	const PhysicsType physics = PhysicsType::BACKWARD_EULER;

	switch (physics)
	{
	case PhysicsType::FORWARD_EULER:
		{
			// EXPLICIT EULER (FORWARD EULER)

			position = position + velocity * frameTime.asSeconds();
			velocity = velocity + acceleration * frameTime.asSeconds();

			// drag
			velocity = velocity * DRAG_MULT;

			// Update acceleration
			UpdateAcceleration();
		}
		break;

	case PhysicsType::BACKWARD_EULER:
		{
			// IMPLICIT / BACKWARD EULER

			// Update acceleration
			UpdateAcceleration();

			velocity = velocity + acceleration * frameTime.asSeconds();

			// drag
			velocity = velocity * DRAG_MULT;

			position = position + velocity * frameTime.asSeconds();

		}
		break;

	default:
		break;
	}
	 

	// Update the visual position to match the physics simulation
	sprite.setPosition(position);
}

void Player::UpdateAcceleration()
{
	const float ACCEL = 1000;

	// Update acceleration
	acceleration.x = 0;
	acceleration.y = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		acceleration.x = -ACCEL;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		acceleration.x = ACCEL;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		acceleration.y = -ACCEL;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		acceleration.y = ACCEL;
	}
}



