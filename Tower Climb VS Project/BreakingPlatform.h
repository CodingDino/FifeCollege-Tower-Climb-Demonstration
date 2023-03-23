#pragma once
#include "Platform.h"
class BreakingPlatform :
    public Platform
{

public: 
    BreakingPlatform(sf::Vector2f startingPos);

    void HandleCollision(SpriteObject& _other) override;

};

