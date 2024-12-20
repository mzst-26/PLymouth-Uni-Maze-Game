#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/game.h" // Include the Game class header
#include "../include/button.h" // Include the Button class header

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    // Create a render window
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Mystery Maze - Main Menu");
    
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
    Button playButton(sf::Vector2f(550, 200), "Start"); // Center of the window with text "Start"

    // sor a smoother transition setup
    bool loading = false; // Loading state
    sf::Clock loadingClock; // Clock to delay loading 

    // Fade rectangle setup
    sf::RectangleShape fadeRect(sf::Vector2f(1200, 800)); // Full window size
    fadeRect.setFillColor(sf::Color(0, 0, 0, 0)); // Start fully transparent

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
                    // Update the button state
                    playButton.update(window); // Call update here
                    if (playButton.isPressed()) {
                        std::cout << "Button clicked!\n"; // Debug output
                        loading = true; // Set loading state
                        loadingClock.restart(); // Restart the clock
                    }
                }
            }
        }

        playButton.update(window); // Update the button state continuously

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
                    game.run(); // Call the run method to start the game
                    window.close(); // Close the menu window
                };
            }
        }

        // Clear window and draw everything
        window.clear();
        window.draw(background); // Draw the background
        playButton.render(window); // Render the button
        if (loading) {
            window.draw(fadeRect); // Draw the fade rectangle
        }
        window.display();
    }

    return 0;
}