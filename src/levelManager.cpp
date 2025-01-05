#include "../include/levelManager.h"
#include "../include/game.h"
#include <iostream>
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
      timeLimit(120){
// Initialize maze dimensions
 adjustMazeDimensions();
    // Get the current working directory
    std::string currentDir = std::filesystem::current_path().string();

// Example: Save file in the user's Documents folder
    std::string documentsPath = currentDir +  "/save.txt";
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

#include <algorithm> // For std::min and std::max

void LevelManager::adjustMazeDimensions() {
    // Default settings
    int baseWidth = 10, baseHeight = 8;
    int growthRateWidth = 2, growthRateHeight = 2;
    int maxWallsToRemove = 60;

    if (difficulty == "Easy") {
        baseWidth = 10;
        baseHeight = 8;
        growthRateWidth = 2;
        growthRateHeight = 2;
        mazeWallRemovalAmount = std::min(8 + currentLevel * 2, maxWallsToRemove);

        if (currentLevel <= 3) {
            amountOfenemy = 1;
            enemySpeed = 200;
        } else {
            amountOfenemy = 2;
            enemySpeed = 170;
        }
    } else if (difficulty == "Medium") {
        baseWidth = 15;
        baseHeight = 10;
        growthRateWidth = 3;
        growthRateHeight = 3;
        mazeWallRemovalAmount = std::min(15 + currentLevel * 3, maxWallsToRemove);

        if (currentLevel <= 3) {
            amountOfenemy = 2;
            enemySpeed = 160;
        } else {
            amountOfenemy = 4;
            enemySpeed = 150;
        }
    } else if (difficulty == "Hard") {
        baseWidth = 20;
        baseHeight = 16;
        growthRateWidth = 5;
        growthRateHeight = 5;
        mazeWallRemovalAmount = std::min(25 + currentLevel * 5, maxWallsToRemove);

        if (currentLevel <= 3) {
            amountOfenemy = 3;
            enemySpeed = 150;
        } else {
            amountOfenemy = 5;
            enemySpeed = 140;
        }
    } else {
        std::cout << "Invalid difficulty level. Using default settings." << std::endl;
        return;
    }

    // Calculate and clamp maze dimensions
    mazeWidth = std::min(baseWidth + currentLevel * growthRateWidth, 30);
    mazeHeight = std::min(baseHeight + currentLevel * growthRateHeight, 25);

    // // Debug output
    // std::cout << "Level: " << currentLevel
    //           << " Difficulty: " << difficulty
    //           << " Maze Size: " << mazeWidth << "x" << mazeHeight
    //           << " Enemies: " << amountOfenemy
    //           << " Speed: " << enemySpeed
    //           << " Walls Removed: " << mazeWallRemovalAmount
    //           << " Stars: " << stars << std::endl;
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

int LevelManager::getUserScore() const
{
    return userScore;
}
void LevelManager::setUserScore(int addToUserScore) 
{
    userScore += addToUserScore;

}
int LevelManager::getGameStars() const
{
     return stars;
}
void LevelManager::setGameStars(int amountOfStars) 
{
    stars = amountOfStars;
}
int LevelManager::getTimerLimit() const
{
    //  std::cout << timeLimit << "\n";
     return timeLimit;
}
double LevelManager::setTimerLimit(double RemainingTime)
{
    // std::cout << timeLimit << "\n"<< RemainingTime << "\n";
     timeLimit = RemainingTime;
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
std::string LevelManager::getCurrentDiff()  {
    return difficulty;
}

void LevelManager::calculateStars(int remainingTime) {
    // Calculate the total time available for the level
    int totalTime = 120;

    // Calculate the time taken by the player to complete the level
    int timeTaken = totalTime - remainingTime;

    // Calculate the percentage of time taken by the player
    float percentage = (static_cast<float>(timeTaken) / totalTime) * 100;
    std::cout <<"persentage:" << percentage;
    // Assign stars based on the percentage
    if (percentage <= 30) {
        setGameStars(3); // 3 stars for completing within 40% of the total time
    } else if (percentage <= 50) {
        setGameStars(2); // 2 stars for completing within 50% of the total time
    } else {
        setGameStars(1); // 1 star for completing within the remaining time
    }

    std::cout << "Stars awarded: " << getGameStars() << std::endl;
}

void LevelManager::saveGameState(const sf::Vector2i& playerPos, const sf::Vector2i& exitPosition, 
                                 const std::vector<sf::Vector2i>& enemyPositions, 
                                 const std::vector<sf::Vector2i>& applesPositions, 
                                 int remainingTime, int userScore, sf::Vector2i& mazeStartPos) {
    std::ofstream saveFile(saveFilePath);
    if (saveFile.is_open()) {
        // Save level and maze dimensions
        saveFile << "CurrentLevel:" << currentLevel << "\n";
        saveFile << "MazeWidth:" << mazeWidth << "\n";
        saveFile << "MazeHeight:" << mazeHeight << "\n";

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

        // Save remaining time and total rewards
        saveFile << "RemainingTime:" << remainingTime << "\n";
        saveFile << "userScore:" << userScore << "\n";
         
         // Save maze starting position
        saveFile << "MazeStartPos:" << mazeStartPos.x << "," << mazeStartPos.y << "\n";

        saveFile.close();
        isGameSaved = true;
        std::cout << "Game state saved successfully.\n";
    } else {
        std::cerr << "Error: Unable to save game state to file.\n";
    }
}


void LevelManager::loadGameState(sf::Vector2i& playerPos, sf::Vector2i& exitPosition,
                                 std::vector<sf::Vector2i>& enemyPositions,
                                 std::vector<sf::Vector2i>& applesPositions,
                                 int& remainingTime, int& userScore, sf::Vector2i& mazeStartPos) {
    std::ifstream saveFile(saveFilePath);
    if (saveFile.is_open()) {
        std::string line;
        while (std::getline(saveFile, line)) {
            std::cout << "Parsing line: " << line << std::endl;

            std::istringstream iss(line);
            std::string key, value;
            if (std::getline(iss, key, ':') && std::getline(iss, value)) {
                try {
                    if (key == "CurrentLevel") {
                        currentLevel = std::stoi(value);
                    } else if (key == "MazeWidth") {
                        mazeWidth = std::stoi(value);
                    } else if (key == "MazeHeight") {
                        mazeHeight = std::stoi(value);
                    } else if (key == "PlayerPosition") {
                        auto commaPos = value.find(',');
                        if (commaPos == std::string::npos) throw std::invalid_argument("Missing comma");
                        playerPos.x = std::stoi(value.substr(0, commaPos));
                        playerPos.y = std::stoi(value.substr(commaPos + 1));
                    } else if (key == "Exit") {
                        auto commaPos = value.find(',');
                        if (commaPos == std::string::npos) throw std::invalid_argument("Missing comma");
                        exitPosition.x = std::stoi(value.substr(0, commaPos));
                        exitPosition.y = std::stoi(value.substr(commaPos + 1));
                    } else if (key == "EnemyPositions") {
                        enemyPositions.clear();
                        std::istringstream enemyStream(value);
                        std::string enemyPos;
                        while (std::getline(enemyStream, enemyPos, '|')) {
                            auto commaPos = enemyPos.find(',');
                            if (commaPos == std::string::npos) throw std::invalid_argument("Missing comma in enemy position");
                            enemyPositions.emplace_back(std::stoi(enemyPos.substr(0, commaPos)),
                                                        std::stoi(enemyPos.substr(commaPos + 1)));
                        }
                    } else if (key == "ApplesPositions") {
                        applesPositions.clear();
                        std::istringstream appleStream(value);
                        std::string applePos;
                        while (std::getline(appleStream, applePos, '|')) {
                            auto commaPos = applePos.find(',');
                            if (commaPos == std::string::npos) throw std::invalid_argument("Missing comma in apple position");
                            applesPositions.emplace_back(std::stoi(applePos.substr(0, commaPos)),
                                                         std::stoi(applePos.substr(commaPos + 1)));
                        }
                    } else if (key == "RemainingTime") {
                        remainingTime = std::stoi(value);
                    } else if (key == "userScore") {
                        userScore = std::stoi(value);
                    } else if (key == "MazeStartPos") {
                        auto commaPos = value.find(',');
                        if (commaPos == std::string::npos) throw std::invalid_argument("Missing comma in maze start position");
                        mazeStartPos.x = std::stoi(value.substr(0, commaPos));
                        mazeStartPos.y = std::stoi(value.substr(commaPos + 1));
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Error parsing key: " << key << ", value: " << value << ". Exception: " << e.what() << std::endl;
                }
            } else {
                std::cerr << "Error: Malformed line: " << line << std::endl;
            }
        }
        saveFile.close();
        isGameSaved = true;
        std::cout << "Game state loaded successfully.\n";
    } else {
        std::cerr << "Error: Unable to load game state from file.\n";
    }
}

