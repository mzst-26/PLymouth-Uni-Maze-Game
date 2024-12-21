#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/game.h" // Include the Game class header
#include "../include/button.h" // Include the Button class header
#include "../include/settingsPopup.h" 
#include "../include/levelManager.h"
int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    // Create a render window
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Mystery Maze - Main Menu");

    //instance of Level Manager
    LevelManager levelManager;

    // Load background texture
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("/Users/mobinzaki/Documents/GitHub/PLymouth-Uni-Maze-Game/assets/Backgrounds/MazeImageBackground.png")) {
        std::cerr << "Error loading background image!" << std::endl;
        return -1;
    }
    sf::Sprite background(backgroundTexture);

    // Scale the background to fit the window
    background.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    // Initialize the button from button.h
    Button playButton(sf::Vector2f(550, 200), "NewPlay"); // Center of the window with text "Start"
    Button ResumeButton(sf::Vector2f(550, 260), "Resume"); 
    Button SettingsButton(sf::Vector2f(550, 320), "Settings");
    Button QuitButton(sf::Vector2f(550, 380), "Quit");
    
    // sor a smoother transition setup
    bool loading = false; // Loading state
    sf::Clock loadingClock; // Clock to delay loading 

    // Fade rectangle setup
    sf::RectangleShape fadeRect(sf::Vector2f(1200, 800)); // Full window size
    fadeRect.setFillColor(sf::Color(0, 0, 0, 0)); // Start fully transparent

 
     // Create settings popup instance
    SettingsPopup settingsPopup(window);
    bool showSettings = false; // Control visibility of settings popup

    // Main menu loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Check for button click
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "Mouse clicked at: (" << event.mouseButton.x << ", " << event.mouseButton.y << ")\n";
             
                    if (playButton.isPressed(window)) {
                        std::cout << "Button clicked!\n"; // Debug output
                        loading = true; // Set loading state
                        loadingClock.restart(); // Restart the clock
                    }
                    if (ResumeButton.isPressed(window)) {
                        std::cout << "Resume Button clicked!\n"; // Debug output
                        // TODO: Implement resume logic here
                    }
                    if (SettingsButton.isPressed(window)) {
                        std::cout << "Settings Button CLicked!\n"; // Debug output
                        showSettings = !showSettings; // Toggle settings popup visibility
                    }
                    if (QuitButton.isPressed(window)) {
                        std::cout << "Quit Button CLicked!\n"; // Debug output
                        window.close();
                        window.close();
                    }
                }
            }
            // Handle settings input if the popup is shown
            if (showSettings) {
                settingsPopup.handleInput(event, levelManager); // Process events for settings popup
            }
        }

        // Update button states
        playButton.update(window); // Update the button state continuously
        ResumeButton.update(window); // Update the button state continuously
        SettingsButton.update(window);
        QuitButton.update(window); // Update the button state continuously

        // If loading, simulate a delay and start the game
        if (loading) {
            // Fade in effect
            sf::Color fadeColor = fadeRect.getFillColor();
            if (fadeColor.a < 255) {
                fadeColor.a += 5; // Increase alpha for fade effect
                fadeRect.setFillColor(fadeColor);
            } else {
                if (loadingClock.getElapsedTime().asSeconds() >= 2.0f) {
                    // Initialize the game after fade is complete
                    Game game; // Create a Game object
                    game.run(levelManager); // Call the run method to start the game
                    window.close(); // Close the menu window
                };
            }
        }

        // Clear window and draw everything
        window.clear();
        window.draw(background); // Draw the background
        playButton.render(window); // Render the button
        ResumeButton.render(window); // Render the resume button
        SettingsButton.render(window); // Render the settings button
        QuitButton.render(window); // Render the quit button
        
        if (showSettings) {
            settingsPopup.render(); // Render the settings popup if it's visible
        }

        if (loading) {
            window.draw(fadeRect); // Draw the fade rectangle
        }

        window.display(); // Display everything
    }

    return 0;
}
