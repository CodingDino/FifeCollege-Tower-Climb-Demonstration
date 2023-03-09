#include "SpriteObject.h"

SpriteObject::SpriteObject()
	: sprite()
{
}

void SpriteObject::Update(sf::Time frameTime)
{
}

void SpriteObject::Draw(sf::RenderTarget& target)
{
	target.draw(sprite);
}
