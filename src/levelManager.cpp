#include "../include/levelManager.h"
#include <iostream>
#include "../include/game.h"

LevelManager::LevelManager()
    : currentLevel(1), 
      difficulty("Easy"), // Use the instance
      mazeWidth(10),
      mazeHeight(8),
      amountOfenemy(1),
      enemySpeed(500),
      mazeWallRemovalAmount(8),
      userScore(0),
      stars(0){
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
    if (difficulty == "Easy" && currentLevel <=3 ) {
        mazeWidth = 10 + currentLevel * 2;  // Easy: Small maze grows slowly
        mazeHeight = 8 + currentLevel * 2;
        stars = 1;
        std::cout<<"Easy number 1";
    }else if (difficulty == "Easy" && currentLevel > 3 ) {
        amountOfenemy = 2;
        enemySpeed = 170;
        mazeWallRemovalAmount = 8;
        mazeWidth = 10 + currentLevel * 2;  // Easy: Small maze grows slowly
        mazeHeight = 8 + currentLevel * 2;
        std::cout<<"Easy number 2";
    } else if (difficulty == "Medium" && currentLevel <=3) {
        amountOfenemy = 2;
        enemySpeed = 160;
        mazeWallRemovalAmount = 20;
        mazeWidth = 15 + currentLevel * 3; // Medium: Moderate maze growth
        mazeHeight = 10 + currentLevel * 3;
    } else if (difficulty == "Medium" && currentLevel > 3) {
        amountOfenemy = 3;
        enemySpeed = 150;
        mazeWallRemovalAmount = 25;
        mazeWidth = 15 + currentLevel * 3; // Medium: Moderate maze growth
        mazeHeight = 10 + currentLevel * 3;
    } else if (difficulty == "Hard" && currentLevel <=3) {
        amountOfenemy = 3;
        enemySpeed = 150;
        mazeWallRemovalAmount = 25;
        mazeWidth = 20 + currentLevel * 5; // Hard: Larger maze, grows quickly
        mazeHeight = 16 + currentLevel * 5;
    }else if (difficulty == "Hard" && currentLevel > 3) {
        amountOfenemy = 4;
        enemySpeed = 140;
        mazeWallRemovalAmount = 30;
        mazeWidth = 20 + currentLevel * 5; // Hard: Larger maze, grows quickly
        mazeHeight = 16 + currentLevel * 5;
    } else {
        std::cout << "Invalid difficulty level. Using default settings." << std::endl;
    }
}

void LevelManager::resetLevelState() {
    // Reset variables for the new level
    std::cout << "Resetting level-specific state..." << std::endl;
}
int LevelManager::getEnemyGenerateAmount() const{
     return amountOfenemy;
}
int LevelManager::getEnemySpeed() const{
     return enemySpeed;
}
int LevelManager::getMazeWallRemovalAmount() const{
     return mazeWallRemovalAmount;
}

std::string LevelManager::getUserScore() const
{
    return std::to_string(userScore);
}
int LevelManager::getGameStars() const{
     return stars;
}
void LevelManager::update()
{
    // Update level-specific logic here
}

void LevelManager::render(sf::RenderWindow& window) {
    // Render the current level here
    // Draw maze, player, enemy, and other level elements
}

int LevelManager::getMazeWidth() const
{
    return mazeWidth;
}

int LevelManager::getMazeHeight() const {
    return mazeHeight;
}

int LevelManager::getCurrentLevel() const {
    return currentLevel;
}

