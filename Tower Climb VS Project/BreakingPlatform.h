#pragma once
#include "Platform.h"
class BreakingPlatform :
    public Platform
{

public: 
    BreakingPlatform();

    void HandleCollision(SpriteObject _other) override;

};

