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
	, twoFramesOldPos(100,300)
	, velocity(0,0)
	, acceleration(0,0)
	, shouldJump(false)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/PlayerStand.png"));
	sprite.setPosition(GetPosition());

	collisionScale = sf::Vector2f(0.5f, 0.70f);
	collisionOffset = sf::Vector2f(0, 20);
	collisionType = CollisionType::AABB;
}

void Player::Update(sf::Time frameTime)
{
	if (!alive)
		return;

	const float DRAG_MULT = 10.0f;
	const PhysicsType physics = PhysicsType::FORWARD_EULER;

	switch (physics)
	{
	case PhysicsType::FORWARD_EULER:
		{
			// EXPLICIT EULER (FORWARD EULER)

			SetPosition( GetPosition() + velocity * frameTime.asSeconds());
			velocity = velocity + acceleration * frameTime.asSeconds();

			// drag
			velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();

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
			velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();

			SetPosition( GetPosition() + velocity * frameTime.asSeconds());

		}
		break;

	case PhysicsType::SYMPLECTIC_EULER:
		{
			// SEMI-IMPLICIT / SYMPLECTIC_EULER

			velocity = velocity + acceleration * frameTime.asSeconds();

			// drag
			velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();

			SetPosition( GetPosition() + velocity * frameTime.asSeconds());

			// Update acceleration
			UpdateAcceleration();
		}
		break;

	case PhysicsType::POSITION_VERLET:
	{
		// Update acceleration
		UpdateAcceleration();

		sf::Vector2f lastFramePos = GetPosition();

		// Calculate current fram's position
		SetPosition( 2.0f*lastFramePos - twoFramesOldPos + acceleration * frameTime.asSeconds() * frameTime.asSeconds());

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
		SetPosition( GetPosition() + halfFrameVelocity * frameTime.asSeconds());

		// Update our current acceleration
		UpdateAcceleration();

		// Get new frame's velocity using half frame velocity and
		// updated acceleration
		velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;

		// drag
		velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();
	}
	break;

	default:
		break;
	}

	SpriteObject::Update(frameTime);
}

void Player::HandleCollision(SpriteObject& _other)
{
	if (_other.GetSolid())
	{
		sf::Vector2f depth = GetCollisionDepth(_other);
		sf::Vector2f newPos = GetPosition();

		if (abs(depth.x) < abs(depth.y))
		{
			// Move on x axis
			newPos.x += depth.x;
			velocity.x = 0;
			acceleration.x = 0;
		}
		else
		{
			// If we were falling and we collided in the y direction and we're on the top side of the platform...
			if (velocity.y > 0)//&& depth.y < 0)
			{
				shouldJump = true;
			}

			// Move on y axis
			newPos.y += depth.y;
			velocity.y = 0;
			acceleration.y = 0;
		}

		SetPosition(newPos);
	}
	SpriteObject::HandleCollision(_other);
}

void Player::UpdateAcceleration()
{
	const float ACCEL = 5000;
	const float GRAVITY = 1000;
	const float JUMP = 1000;

	// Update acceleration
	acceleration.x = 0;
	acceleration.y = GRAVITY;
	if (shouldJump)
	{
		velocity.y = -JUMP;
		shouldJump = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		acceleration.x = -ACCEL;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		acceleration.x = ACCEL;
	}
}



