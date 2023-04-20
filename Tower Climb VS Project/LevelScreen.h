#pragma once
#include "Screen.h"
#include "Player.h"
#include "Door.h"
#include <SFML/Graphics.hpp>

class Game;
class Platform;

class LevelScreen :
    public Screen
{

public:
    LevelScreen(Game* newGamePointer);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;

    void LoadNextLevel();
    void LoadLevel(int levelNumber);
    bool LoadLevel(std::string fileName);


private:

    Player player;
    std::vector<Platform*> platforms;
    Door door;

    sf::View camera;

    int currentLevel;

};

