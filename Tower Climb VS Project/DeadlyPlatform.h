
#include "Platform.h"


class DeadlyPlatform :
    public Platform
{

public:
    DeadlyPlatform();

    void HandleCollision(SpriteObject& _other) override;
};
