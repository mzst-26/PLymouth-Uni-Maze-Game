#include "../include/settingsPopup.h"
#include "../include/button.h"
#include <filesystem>
#include <iostream>


SettingsPopup::SettingsPopup(sf::RenderWindow& window)
    : window(window),
      easyButton(sf::Vector2f(500, 440), "Easy"),
      mediumButton(sf::Vector2f(550, 440), "Medium"),
      hardButton(sf::Vector2f(600, 440), "Hard"),
      activeButtonIndex(0),
      currentDifficulty() {
     
     // Get the current working directory
    std::string currentDir = std::filesystem::current_path().string();

     // Load font for title text
    if (!titleFont.loadFromFile(currentDir + "/assets/fonts/font.ttf")) {
        std::cerr << "Error: Could not load font!" << std::endl;
    }

    // Set up title text
    titleText.setFont(titleFont);
    titleText.setString("Difficulty: Easy");
    titleText.setCharacterSize(24);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(200, 440); // Position slightly above the buttons
}


void SettingsPopup::render() {
    // Render all buttons
    easyButton.render(window);
    mediumButton.render(window);
    hardButton.render(window);

    // Draw the updated title text
    window.draw(titleText);
}


void SettingsPopup::handleInput(const sf::Event& event, LevelManager& levelManager) {
// Create an instance of SettingsPopup
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
        if (easyButton.isPressed(window)) {
            // Activate Easy button
            easyButton.setButtonState(PRESSED);
            mediumButton.setButtonState(IDLE);
            hardButton.setButtonState(IDLE);
            activeButtonIndex = 0;
            currentDifficulty = "Easy";
            std::cout << "Active button: Easy" << std::endl;
            titleText.setString("Difficulty: Easy");
            easyButton.setScale(sf::Vector2f(1.2, 1.2));
            mediumButton.setScale(sf::Vector2f(1,1));
            hardButton.setScale(sf::Vector2f(1,1));
            levelManager.setDifficulty(currentDifficulty);
        } else if (mediumButton.isPressed(window)) {
            // Activate Medium button
            easyButton.setButtonState(IDLE);
            mediumButton.setButtonState(PRESSED);
            hardButton.setButtonState(IDLE);

            activeButtonIndex = 1;
            currentDifficulty = "Medium";
            std::cout << "Active button: Medium" << std::endl;
            titleText.setString("Difficulty: Medium");

            easyButton.setScale(sf::Vector2f(1, 1));
            mediumButton.setScale(sf::Vector2f(1.2,1.2));
            hardButton.setScale(sf::Vector2f(1,1));
            levelManager.setDifficulty(currentDifficulty);
        } else if (hardButton.isPressed(window)) {
            // Activate Hard button
            easyButton.setButtonState(IDLE);
            mediumButton.setButtonState(IDLE);
            hardButton.setButtonState(PRESSED);
            activeButtonIndex = 2;
            currentDifficulty = "Hard";
            titleText.setString("Difficulty: Hard");
            std::cout << "Active button: Hard" << std::endl;
            easyButton.setScale(sf::Vector2f(1,1));
            mediumButton.setScale(sf::Vector2f(1,1));
            hardButton.setScale(sf::Vector2f(1.2,1.2));
            levelManager.setDifficulty(currentDifficulty);
        }

        }
    }
      //render and update the button
      render();
      easyButton.update(window);
      mediumButton.update(window);
      hardButton.update(window);
      window.draw(titleText);



}
//External 
std::string SettingsPopup::getCurrentDifficulty() const {
    return currentDifficulty;

}   
