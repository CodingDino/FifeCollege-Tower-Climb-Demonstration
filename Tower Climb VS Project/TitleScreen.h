#pragma once
#include "Screen.h"
#include <SFML/Graphics.hpp>

class Game;

class TitleScreen :
    public Screen
{

public:
    TitleScreen(Game* newGamePointer);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;
};

