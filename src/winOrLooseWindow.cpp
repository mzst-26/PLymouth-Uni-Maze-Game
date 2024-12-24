#include <SFML/Graphics.hpp>
#include <string>
#include "../include/winOrLoosePopup.h"
#include "../include/button.h"
#include "../include/game.h"
#include "../include/levelManager.h"
#include "../include/star.h"
#include "../include/scoreBoard.h"
// Function to create a popup popupWindow
void WinOrLoose::createWinOrLoosePopupWindow(const std::string& message, const sf::Color& bgColor, LevelManager& levelManager, sf::RenderWindow& window) {
    sf::Vector2u windowSize;
    sf::Vector2f restartPosition;
    int messagePosition = 300;
    if (message == "Game Over") {
        windowSize = sf::Vector2u(400, 200);
        restartPosition =sf::Vector2f(168, 131);
        messagePosition -= 200;
    } else {
        windowSize = sf::Vector2u(400, 500);
        restartPosition =sf::Vector2f(202, 434);
    }

    // Create the popup window
    sf::RenderWindow popupWindow(sf::VideoMode(windowSize.x, windowSize.y), "Maze Game", sf::Style::Titlebar | sf::Style::Close);

    std::string rewardAmount = levelManager.getUserScore();
    int currentLevel = levelManager.getCurrentLevel();
    int gameStars = levelManager.getGameStars();
    //Create Scoreboard
    ScoreBoard scoreBoard(sf::Vector2f(45, 140), "Board", rewardAmount);

    //initialise Stars
    Star oneStar(sf::Vector2f(115,25), "Star");
    Star twoStar(sf::Vector2f(167,10), "Star");
    Star threeStar(sf::Vector2f(232,25), "Star");
    //set their scale
    oneStar.setScale(sf::Vector2f(0.4f,0.4f));
    twoStar.setScale(sf::Vector2f(0.5f,0.5f));
    threeStar.setScale(sf::Vector2f(0.4f,0.4f));
    
    //initialise the buttons to move on if the player wins or restart if player looses
    Button nextlevel(sf::Vector2f(132, 434), "NextLevel"); // Center of the popupWindow with text "Start"
    Button restart(sf::Vector2f(restartPosition), "Restart"); // Center of the popupWindow with text "Start"
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

    //set up level visualiser in text
    sf::Text levelText;
    levelText.setFont(font);
    levelText.setCharacterSize(18);
    levelText.setFillColor(sf::Color::White);
    levelText.setStyle(sf::Text::Bold);
    levelText.setPosition(170, 100);
    if (message != "Game Over"){
        levelText.setString("Level: " + std::to_string(currentLevel + 1) );
    }else{
                levelText.setString("Level: " + std::to_string(currentLevel) );
    }

    // Set up star visualiser
    sf::Sprite starSprite;

    // Center the text
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(200, messagePosition);

    // Run the popupWindow loop
    while (popupWindow.isOpen()) {
        sf::Event event;
        while (popupWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                popupWindow.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                if (restart.isPressed(popupWindow)){
                    // Restart the game
                    popupWindow.close();
                    Game game(window); // Create a Game object
                    game.run(levelManager, levelManager.getTimerLimit()); // Call the run method to start the game
                    return;
                }
                if (nextlevel.isPressed(popupWindow)){
                    // Move to the next level
                    int currentLevel = levelManager.getCurrentLevel();
                    levelManager.loadLevel(currentLevel + 1);
                    popupWindow.close();
                    Game game(window); // Create a Game object
                    game.run(levelManager, levelManager.getTimerLimit()); // Call the run method to start the game
                    return;
                }
            }
        }

             //set their state based on the level manage getGameStar
        for(int i = 0; i < gameStars; i++) {
            if(i == 0) {
                oneStar.setActive();
            } else if(i == 1) {
                oneStar.setActive();
                twoStar.setActive();
            } else if(i == 2) {
                oneStar.setActive();
                twoStar.setActive();
                threeStar.setActive();
            }
        }

        // Clear and redraw
        popupWindow.clear(bgColor);
        popupWindow.draw(text);
        popupWindow.draw(levelText);
       

        // Update button states
        if(message == "Lucky Day for You"){
            nextlevel.update(popupWindow);
            nextlevel.render(popupWindow);
            // Draw stars
            oneStar.render(popupWindow);
            twoStar.render(popupWindow);
            threeStar.render(popupWindow);
            scoreBoard.render(popupWindow);
        }
       
        restart.update(popupWindow);
        restart.render(popupWindow);
       
    
         popupWindow.display();
    }
}

// Function to display the "Game Over" popup
void WinOrLoose::showGameOverPopup(LevelManager& levelManager, sf::RenderWindow& window) {
    createWinOrLoosePopupWindow("Game Over", sf::Color::Red, levelManager, window);
}

// Function to display the "Lucky Day for You" popup
void WinOrLoose::showLuckyDayPopup(LevelManager& levelManager, sf::RenderWindow& window) {
    createWinOrLoosePopupWindow("Lucky Day for You", sf::Color::Green, levelManager, window);
}