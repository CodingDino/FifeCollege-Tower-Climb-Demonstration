#pragma once
#include <SFML/Graphics.hpp>

class SpriteObject
{
public:

	SpriteObject();

	virtual void Update(sf::Time frameTime);
	virtual void Draw(sf::RenderTarget& target);

	void SetPosition(float posX, float posY);
	void SetPosition(sf::Vector2f _position);
	sf::Vector2f GetPosition();

	sf::Vector2f GetBoundingCircleCentre();
	float GetBoundingCircleRadius();


protected:

	sf::Sprite sprite;

	// physics settings

private:
	sf::Vector2f position;

};

