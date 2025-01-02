#include "../include/levelManager.h"
#include <iostream>
#include "../include/game.h"
#include <filesystem>
#include <fstream>
#include <sstream>

LevelManager::LevelManager()
    : currentLevel(1), 
      difficulty("Easy"), // Use the instance
      mazeWidth(10),
      mazeHeight(8),
      amountOfenemy(1),
      enemySpeed(500),
      mazeWallRemovalAmount(8),
      userScore(0),
      stars(0),
      timeLimit(2){
// Initialize maze dimensions
 adjustMazeDimensions();

 // Example: Save file in the user's Documents folder
    std::string documentsPath = "/Users/mobinzaki/Documents/save.txt";
    saveFilePath = documentsPath;

    // Create the directory if it doesn't exist
    std::filesystem::create_directory(std::filesystem::path(documentsPath).parent_path());


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
        amountOfenemy = 1;
        mazeWallRemovalAmount = 8;
        enemySpeed = 200;
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
int LevelManager::getEnemyGenerateAmount() const {
    // Check the current difficulty and return the appropriate amount of enemies
    if (difficulty == "Easy") {
        return (currentLevel <= 3) ? 1 : 2; // 1 enemy for levels 1-3, 2 for levels 4+
    } else if (difficulty == "Medium") {
        return (currentLevel <= 3) ? 2 : 3; // 2 enemies for levels 1-3, 3 for levels 4+
    } else if (difficulty == "Hard") {
        return (currentLevel <= 3) ? 3 : 4; // 3 enemies for levels 1-3, 4 for levels 4+
    } else {
        std::cout << "Invalid difficulty level. Returning default value." << std::endl;
        return 1; // Default value if difficulty is invalid
    }
}
int LevelManager::getEnemySpeed() const
{
     return enemySpeed;
}
int LevelManager::getMazeWallRemovalAmount() const
{
     return mazeWallRemovalAmount;
}

std::string LevelManager::getUserScore() const
{
    return std::to_string(userScore);
}
int LevelManager::getGameStars() const
{
     return stars;
}
int LevelManager::getTimerLimit() const
{
     return timeLimit;
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

void LevelManager::saveGameState(const sf::Vector2i& playerPos, const sf::Vector2i& exitPosition, const std::vector<sf::Vector2i>& enemyPositions, const std::vector<sf::Vector2i>& applesPositions, int remainingTime) {
    std::ofstream saveFile(saveFilePath);
    if (saveFile.is_open()) {
        // Save player position
        saveFile << "PlayerPosition:" << playerPos.x << "," << playerPos.y << "\n";

        // Save exit position
        saveFile << "Exit:" << exitPosition.x << "," << exitPosition.y << "\n";

        // Save enemy positions
        saveFile << "EnemyPositions:";
        for (size_t i = 0; i < enemyPositions.size(); ++i) {
            saveFile << enemyPositions[i].x << "," << enemyPositions[i].y;
            if (i < enemyPositions.size() - 1) saveFile << "|";
        }
        saveFile << "\n";

        // Save apples positions
        saveFile << "ApplesPositions:";
        for (size_t i = 0; i < applesPositions.size(); ++i) {
            saveFile << applesPositions[i].x << "," << applesPositions[i].y;
            if (i < applesPositions.size() - 1) saveFile << "|";
        }
        saveFile << "\n";

        // Save remaining time
        saveFile << "RemainingTime:" << remainingTime << "\n";

        saveFile.close();
        isGameSaved = true;
         std::cerr << "saved game state to file.\n";
    } else {
        std::cerr << "Error: Unable to save game state to file.\n";
    }
}
void LevelManager::loadGameState(sf::Vector2i& playerPos,sf::Vector2i& exitPosition, std::vector<sf::Vector2i>& enemyPositions, std::vector<sf::Vector2i>& applesPositions, int& remainingTime) {
    std::ifstream saveFile(saveFilePath);
    if (saveFile.is_open()) {
        std::string line;
        while (std::getline(saveFile, line)) {
            std::istringstream iss(line);
            std::string key;
            if (std::getline(iss, key, ':')) {
                if (key == "PlayerPosition") {
                    std::string value;
                    std::getline(iss, value);
                    size_t commaPos = value.find(',');
                    playerPos.x = std::stoi(value.substr(0, commaPos));
                    playerPos.y = std::stoi(value.substr(commaPos + 1));
                }else if (key == "Exit") {
                    std::string value;
                    std::getline(iss, value);
                    size_t commaPos = value.find(',');
                    exitPosition.x = std::stoi(value.substr(0, commaPos));
                    exitPosition.y = std::stoi(value.substr(commaPos + 1));
                }
                 else if (key == "EnemyPositions") {
                    std::string value;
                    std::getline(iss, value);
                    std::istringstream enemyStream(value);
                    std::string enemyPos;
                    while (std::getline(enemyStream, enemyPos, '|')) {
                        size_t commaPos = enemyPos.find(',');
                        sf::Vector2i enemy;
                        enemy.x = std::stoi(enemyPos.substr(0, commaPos));
                        enemy.y = std::stoi(enemyPos.substr(commaPos + 1));
                        enemyPositions.push_back(enemy);
                    }
                } else if (key == "ApplesPositions") {
                    std::string value;
                    std::getline(iss, value);
                    std::istringstream appleStream(value);
                    std::string applePos;
                    while (std::getline(appleStream, applePos, '|')) {
                        size_t commaPos = applePos.find(',');
                        sf::Vector2i apple;
                        apple.x = std::stoi(applePos.substr(0, commaPos));
                        apple.y = std::stoi(applePos.substr(commaPos + 1));
                        applesPositions.push_back(apple);
                    }
                } else if (key == "RemainingTime") {
                    std::string value;
                    std::getline(iss, value);
                    remainingTime = std::stoi(value);
                }
            }
        }
        saveFile.close();
        isGameSaved = true;
    } else {
        std::cerr << "Error: Unable to load game state from file.\n";
    }
}
