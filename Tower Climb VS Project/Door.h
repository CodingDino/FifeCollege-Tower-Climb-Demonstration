#pragma once
#include "SpriteObject.h"

// forward declaration
// Allowed because levelsceen is not used in THIS file
// And because it is only a pointer
class LevelScreen;

class Door :
    public SpriteObject
{
public:
    Door(LevelScreen* newLevelScreen);
    void HandleCollision(SpriteObject& other) override;

private:
    LevelScreen* levelScreen;

};

