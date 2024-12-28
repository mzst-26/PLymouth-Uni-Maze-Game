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
    std::string getUserScore() const;
    int getGameStars() const;
    int getTimerLimit() const;
   

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
    int timeLimit; //in min
    void adjustMazeDimensions();   // Adjust maze dimensions based on difficulty and level
    void resetLevelState();  
     // Create an instance of SettingsPopup 


};


#endif //LEVEL_MANAGER_