#pragma once
#include "Platform.h"
class MovingPlatform :
    public Platform
{

public:
    MovingPlatform(sf::Vector2f startingPos, float newMinX, float newMaxX);

    void Update(sf::Time frameTime) override;

private:
    const float SPEED;
    const float MIN_X;
    const float MAX_X;
    float horizontalVel;

};

