
#include "Platform.h"


class DeadlyPlatform :
    public Platform
{

public:
    DeadlyPlatform(sf::Vector2f startingPos);

    void HandleCollision(SpriteObject& _other) override;
};
