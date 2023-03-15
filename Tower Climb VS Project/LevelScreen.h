#pragma once
#include "Screen.h"
#include "Player.h"
#include "Platform.h"
#include "Door.h"
#include <SFML/Graphics.hpp>

class Game;

class LevelScreen :
    public Screen
{

public:
    LevelScreen(Game* newGamePointer);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;


private:

    Player player;
    Platform testPlatform;
    Door testDoor;

};

