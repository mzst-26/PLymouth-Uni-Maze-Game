#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "levelManager.h"

class Game {
public:
    void run(LevelManager& levelManager); // Method to start the game loop
};

#endif // GAME_H