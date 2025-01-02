#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib> 
#include "a_star.h"
#include "settingsPopup.h"
#include "escape.h"
#include "levelManager.h"
#include "winOrLoosePopup.h"
#include "home.h"
#include "modules.h"
#include "apples.h"

class Game {
public:
    Game(sf::RenderWindow& window, std::string gameType); // Constructor to initialize the game with a window
    void run(LevelManager& levelManager, int timeLimitMinutes); // Method to start the game loop
    

private:
    std::string gameType; // Type of game (new game or resume)
    sf::RenderWindow& window; // Reference to the main game window
    bool isPositionOccupied(const sf::Vector2i& pos, const std::vector<sf::Vector2i>& occupiedPositions);

    // Initialize positions and game variables
    int remainingTime;
    sf::Vector2i playerPos;
    sf::Vector2i exitPos;
    std::vector<sf::Vector2i> enemyPositions;
    std::vector<sf::Vector2i> applesPositions;
    std::vector<sf::Vector2i> occupiedPositions;
    std::vector<Enemy> enemies; // Vector to hold multiple enemies
    std::vector<Apples> apples;  // Vector to hold multiple apples
};

#endif // GAME_H