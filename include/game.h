#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "levelManager.h"

class Game {
public:
    Game(sf::RenderWindow& window); // Constructor to initialize the game with a window
    void run(LevelManager& levelManager, int timeLimitMinutes); // Method to start the game loop
 

private:
    sf::RenderWindow& window; // Reference to the main game window
};

#endif // GAME_H