
#ifndef MAIN_H
#define MAIN_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/game.h"        // Include the Game class header
#include "../include/button.h"      // Include the Button class header
#include "../include/settingsPopup.h" 
#include "../include/levelManager.h"

class Home {
public:
    Home(sf::RenderWindow& window); // Constructor
    ~Home(); // Destructor

    void run(LevelManager& levelManager); // Run the main menu loop

private:
    sf::RenderWindow& window;                  // Main menu window
    sf::Texture backgroundTexture;           // Background texture
    sf::Sprite background;                   // Background sprite
    Button playButton;                       // Play button
    Button resumeButton;                     // Resume button
    Button settingsButton;                   // Settings button
    Button quitButton;                       // Quit button
    sf::RectangleShape fadeRect;             // Fade rectangle for transitions
    sf::Clock loadingClock;                  // Clock for loading state
    bool loading;                            // Loading state
    bool showSettings;                       // Flag for settings popup visibility
    SettingsPopup settingsPopup;             // Settings popup

    void handleEvents(LevelManager& levelManager);                     // Handle events
    void update(LevelManager& levelManager);                           // Update menu state
    void render();                           // Render menu items
};

#endif // MAIN_H
