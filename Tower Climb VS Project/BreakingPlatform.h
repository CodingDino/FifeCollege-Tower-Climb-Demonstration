#pragma once
#include "Platform.h"
class BreakingPlatform :
    public Platform
{

public: 
    BreakingPlatform();

    void Draw(sf::RenderTarget& target) override;

private:
    bool alive;
};

