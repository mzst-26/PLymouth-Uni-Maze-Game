#ifndef LEVEL_MANAGER_
#define LEVEL_MANAGER_
#include "../include/settingsPopup.h"
#include <string>
#include <vector>

class LevelManager {
    public:   

    LevelManager();
    void setDifficulty(std::string difficulty); // Set difficulty level
    void loadLevel(int levelNumber);                   // Load a specific level
    void update();                                     // Update level logic
    void render(sf::RenderWindow& window);             // Render the current level

    int getMazeWidth() const;                          // Get maze width
    int getMazeHeight() const;                         // Get maze height
    int getCurrentLevel() const; 
    
    private:
    // Private members and methods go here
    int currentLevel{1};
    std::string difficulty;
    int mazeWidth;                 // Maze width based on difficulty
    int mazeHeight; 
    void adjustMazeDimensions();   // Adjust maze dimensions based on difficulty and level
    void resetLevelState();  
     // Create an instance of SettingsPopup  
};


#endif //LEVEL_MANAGER_