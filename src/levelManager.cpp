#include "../include/levelManager.h"
#include <iostream>



LevelManager::LevelManager()
    : currentLevel(1), 
      difficulty("Easy"), // Use the instance
      mazeWidth(10), 
      mazeHeight(8) {
// Initialize maze dimensions
 adjustMazeDimensions();
}

void LevelManager::setDifficulty(std::string difficulty) {
    this->difficulty = difficulty;
    std::cout << "Setting difficulty to: " << difficulty << std::endl;
    adjustMazeDimensions();
    std::cout << "Maze dimensions: " << mazeWidth << "x" << mazeHeight << std::endl;
}


void LevelManager::loadLevel(int levelNumber) {
    currentLevel = levelNumber;
    adjustMazeDimensions();
    resetLevelState();

    std::cout << "Level " << currentLevel << " loaded with dimensions "
              << mazeWidth << "x" << mazeHeight << std::endl;
}

void LevelManager::adjustMazeDimensions() {
    // Adjust maze size based on difficulty and level
    if (difficulty == "Easy") {
        mazeWidth = 10 + currentLevel * 2;  // Easy: Small maze grows slowly
        mazeHeight = 8 + currentLevel * 2;
    } else if (difficulty == "Medium") {
        mazeWidth = 15 + currentLevel * 3; // Medium: Moderate maze growth
        mazeHeight = 10 + currentLevel * 3;
    } else if (difficulty == "Hard") {
        mazeWidth = 20 + currentLevel * 5; // Hard: Larger maze, grows quickly
        mazeHeight = 16 + currentLevel * 5;
    } else {
        // Default case
        mazeWidth = 10;
        mazeHeight = 10;
        std::cout << "Invalid difficulty level. Using default settings." << std::endl;
    }
}

void LevelManager::resetLevelState() {
    // Reset variables for the new level
    std::cout << "Resetting level-specific state..." << std::endl;
}

void LevelManager::update() {
    // Update level-specific logic here
}

void LevelManager::render(sf::RenderWindow& window) {
    // Render the current level here
    // Draw maze, player, enemy, and other level elements
}

int LevelManager::getMazeWidth() const {
    return mazeWidth;
}

int LevelManager::getMazeHeight() const {
    return mazeHeight;
}

int LevelManager::getCurrentLevel() const {
    return currentLevel;
}
