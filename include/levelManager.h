#ifndef LEVEL_MANAGER_
#define LEVEL_MANAGER_
#include "../include/settingsPopup.h"
#include <string>
#include <vector>

class SettingsPopup;
class LevelManager {
    public:   

    LevelManager();
    void setDifficulty(std::string difficulty); // Set difficulty level
    void loadLevel(int levelNumber);                   // Load a specific level
    void update();                                     // Update level logic
    void render(sf::RenderWindow& window);  // Render the current level
    void handleWinLoose(std::string status);
    int getMazeWidth() const;                          // Get maze width
    int getMazeHeight() const;                         // Get maze height
    int getCurrentLevel() const; 
    int getEnemyGenerateAmount() const;
    int getEnemySpeed()const;
    int getMazeWallRemovalAmount() const;
    int getUserScore() const;
    void setUserScore(int addToUserScore);
    int getGameStars() const;
    void setGameStars(int amountOfStars);
    std::string getCurrentDiff();
    int getTimerLimit() const;
    double setTimerLimit(double RemainingTime );
    void calculateStars(int remainingTime);

    // Game state variables
    sf::Vector2i savedPlayerPosition;
    std::vector<sf::Vector2i> savedEnemyPositions;
    std::vector<sf::Vector2i> savedApplesPositions;
    int savedRemainingTime;
    bool isGameSaved = false;

    // File path for saving game state
    std::string saveFilePath;
    // Methods to save and load game state
    void saveGameState(const sf::Vector2i& playerPos, const sf::Vector2i& exitPosition, 
                       const std::vector<sf::Vector2i>& enemyPositions, 
                       const std::vector<sf::Vector2i>& applesPositions, 
                       int remainingTime, int userScore, sf::Vector2i& mazeStartPos);

    void loadGameState(sf::Vector2i& playerPos, sf::Vector2i& exitPosition, 
                       std::vector<sf::Vector2i>& enemyPositions, 
                       std::vector<sf::Vector2i>& applesPositions, 
                       int& remainingTime, int& userScore, sf::Vector2i& mazeStartPos);
    
    private:
    // Private members and methods go here
    int currentLevel{1};
    std::string difficulty;
    int mazeWidth;   // Maze width based on difficulty
    int mazeHeight; // Maze height based on difficulty
    int amountOfenemy; //number of enemies
    int enemySpeed;//speed of enemy
    int mazeWallRemovalAmount; // number of walls that need to be removed to make the navigation easier in game
    int userScore;//user score in integer
    int stars; //number of stars from 1 to 3
    double timeLimit; //in min
    void adjustMazeDimensions();   // Adjust maze dimensions based on difficulty and level
    void resetLevelState();  
     // Create an instance of SettingsPopup 


};


#endif //LEVEL_MANAGER_