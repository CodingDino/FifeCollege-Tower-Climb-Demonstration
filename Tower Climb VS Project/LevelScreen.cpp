#include "LevelScreen.h"
#include "AssetManager.h"

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, tempSprite()
{
	tempSprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/PlayerStand.png"));
}

void LevelScreen::Update(sf::Time frameTime)
{
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	target.draw(tempSprite);
}
