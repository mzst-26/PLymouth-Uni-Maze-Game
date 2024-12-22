#include <SFML/Graphics.hpp>
#include <string>
#include "../include/winOrLoosePopup.h"
#include "../include/button.h"
#include "../include/game.h"
#include "../include/levelManager.h"
// Function to create a popup window
void createWinOrLoosePopupWindow(const std::string& message, const sf::Color& bgColor, LevelManager& levelManager) {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(400, 200), "Maze Game", sf::Style::Titlebar | sf::Style::Close);
    //initialise the buttons to move on if the player wins or restart if player looses
    int restartPosition;
    if (message != "Game Over"){
        restartPosition = 202;
    }else{
        restartPosition = 168;
    }
    Button nextlevel(sf::Vector2f(132, 131), "NextLevel"); // Center of the window with text "Start"
    Button restart(sf::Vector2f(restartPosition, 131), "Restart"); // Center of the window with text "Start"
    //set their scale
    nextlevel.setScale(sf::Vector2f(1, 1));
    restart.setScale(sf::Vector2f(1, 1));
    // Load font
    sf::Font font;
    if (!font.loadFromFile("/Users/mobinzaki/Documents/GitHub/PLymouth-Uni-Maze-Game/assets/fonts/font.ttf")) {
        // If font loading fails, display error in console and return
       
        return;
    }

    // Set up text
    sf::Text text;
    text.setFont(font);
    text.setString(message);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);

    // Center the text
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(200, 100);

    // Run the window loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                if (restart.isPressed(window)){
                    // Restart the game
                    window.close();
                    Game game; // Create a Game object
                    game.run(levelManager); // Call the run method to start the game
                    window.close();
                    window.close();
                    return;
                }
                if (nextlevel.isPressed(window)){
                    // Restart the game
                    window.close();
                    Game game; // Create a Game object
                    game.run(levelManager); // Call the run method to start the game
                    window.close();
                    window.close();
                    return;
                }
            }
        }

        // Clear and redraw
        window.clear(bgColor);
        window.draw(text);
       

        // Update button states
        if(message == "Lucky Day for You"){
            nextlevel.update(window);
            nextlevel.render(window);
        }
       
        restart.update(window);
        restart.render(window);

         window.display();
    }
}

// Function to display the "Game Over" popup
void showGameOverPopup(LevelManager& levelManager) {
    createWinOrLoosePopupWindow("Game Over", sf::Color::Red, levelManager);
}

// Function to display the "Lucky Day for You" popup
void showLuckyDayPopup(LevelManager& levelManager) {
    createWinOrLoosePopupWindow("Lucky Day for You", sf::Color::Green, levelManager);
}