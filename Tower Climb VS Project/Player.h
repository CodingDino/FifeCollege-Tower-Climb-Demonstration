#pragma once
#include "SpriteObject.h"


class Player :
    public SpriteObject
{

public:

    Player();

    void Update(sf::Time frameTime) override;

    void HandleSolidCollision(SpriteObject _other);

private:

    void UpdateAcceleration();

    sf::Vector2f twoFramesOldPos;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

};

