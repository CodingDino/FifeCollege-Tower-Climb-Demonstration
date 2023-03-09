#include "Player.h"
#include "AssetManager.h"


enum class PhysicsType {
	FORWARD_EULER,
	BACKWARD_EULER,
	SYMPLECTIC_EULER,
	POSITION_VERLET,
	VELOCITY_VERLET
};


Player::Player()
	: SpriteObject()
	, position(100,300)
	, twoFramesOldPos(100,300)
	, velocity(0,0)
	, acceleration(0,0)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/PlayerStand.png"));
	sprite.setPosition(position);
}

void Player::Update(sf::Time frameTime)
{
	const float DRAG_MULT = 0.99f;
	const PhysicsType physics = PhysicsType::VELOCITY_VERLET;

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

	case PhysicsType::SYMPLECTIC_EULER:
		{
			// SEMI-IMPLICIT / SYMPLECTIC_EULER

			velocity = velocity + acceleration * frameTime.asSeconds();

			// drag
			velocity = velocity * DRAG_MULT;

			position = position + velocity * frameTime.asSeconds();

			// Update acceleration
			UpdateAcceleration();
		}
		break;

	case PhysicsType::POSITION_VERLET:
	{
		// Update acceleration
		UpdateAcceleration();

		sf::Vector2f lastFramePos = position;

		// Calculate current fram's position
		position = 2.0f*lastFramePos - twoFramesOldPos + acceleration * frameTime.asSeconds() * frameTime.asSeconds();

		// Two frames ago (for next frame)
		twoFramesOldPos = lastFramePos;
	}
	break;

	case PhysicsType::VELOCITY_VERLET:
	{
		// VELOCITY VERLET / LEAP FROG

		// Get half frame velocity using
		// previous frame's acceleration
		sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;

		// Get new frame's position using half frame velocity
		position = position + halfFrameVelocity * frameTime.asSeconds();

		// Update our current acceleration
		UpdateAcceleration();

		// Get new frame's velocity using half frame velocity and
		// updated acceleration
		velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;

		// drag
		velocity = velocity * DRAG_MULT;
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



