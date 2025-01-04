#include <SFML/Graphics.hpp>
#include <filesystem>
#include <string>
#include "../include/winOrLoosePopup.h"

// Function to create a popup popupWindow
void WinOrLoose::createWinOrLoosePopupWindow(const std::string& message, const sf::Color& bgColor, LevelManager& levelManager, sf::RenderWindow& mainWindow) {
    //for dynamic size and position
    sf::Vector2f popupSize;
    sf::Vector2f restartButtonPosition;
    int messagePosition = 300;
    if (message == "Game Over") {
        popupSize = sf::Vector2f(400.f, 300.f); // Ensure floating-point literals
        restartButtonPosition = sf::Vector2f((mainWindow.getSize().x - 64 )/ 2, (mainWindow.getSize().y - popupSize.y + 550)/2);
        messagePosition -= 200;
    } else {
        popupSize = sf::Vector2f(400.f, 500.f); // Ensure floating-point literals
        restartButtonPosition = sf::Vector2f((mainWindow.getSize().x + 128)/ 2, (mainWindow.getSize().y - popupSize.y + 950)/2);
    }

    // Popup area dimensions and position
    sf::RectangleShape popupArea(popupSize); // Smaller popup
    popupArea.setFillColor(bgColor);
    popupArea.setOutlineColor(sf::Color::White);
    popupArea.setOutlineThickness(3);
    popupArea.setPosition((mainWindow.getSize().x - popupArea.getSize().x) / 2, (mainWindow.getSize().y - popupArea.getSize().y) / 2);

    // Button positions relative to the popup area
    sf::Vector2f popupPosition = popupArea.getPosition();
    // sf::Vector2f restartButtonPosition = popupPosition + sf::Vector2f(60, 200);
    sf::Vector2f nextLevelPosition = popupPosition + sf::Vector2f(70, (mainWindow.getSize().y - popupSize.y + 650)/2);

    // Buttons
    Button restart(restartButtonPosition, "Restart");
    Button nextLevel(nextLevelPosition, "NextLevel");

    //set their scale
    nextLevel.setScale(sf::Vector2f(1, 1));
    restart.setScale(sf::Vector2f(1, 1));

    // Stars and scoreboard
    float starWidth = 50.f; // Adjust based on actual star size
    float spacing = 20.f;   // Space between stars
    int numStars = 3;       // Total number of stars

    // Calculate the total width occupied by all stars and spacing
    float totalStarsWidth = numStars * starWidth + (numStars - 1) * spacing;

    // Calculate the starting x position to center the stars
    float startX = popupPosition.x + (popupArea.getSize().x - totalStarsWidth) / 2;

    // Set positions for each star
    Star oneStar(sf::Vector2f(startX, popupPosition.y - 20), "Star");
    Star twoStar(sf::Vector2f(startX + starWidth + spacing -5, popupPosition.y - 40), "Star");
    Star threeStar(sf::Vector2f(startX + 2 * (starWidth + spacing), popupPosition.y - 20), "Star");

    oneStar.setScale(sf::Vector2f(0.4f, 0.4f));
    twoStar.setScale(sf::Vector2f(0.5f, 0.5f));
    threeStar.setScale(sf::Vector2f(0.4f, 0.4f));

    ScoreBoard scoreBoard(popupPosition + sf::Vector2f(40, 140), "Board", std::to_string(levelManager.getUserScore()));

    // Font for text
    sf::Font font;
    // Get the current working directory
    std::string currentDir = std::filesystem::current_path().string();

    if (!font.loadFromFile(currentDir + "/assets/fonts/font.ttf")) {
        return; // Return early if font loading fails
    }

    // Message text
    sf::Text text(message, font, 24);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.width / 2, textRect.height / 2);
    text.setPosition(popupPosition.x + popupArea.getSize().x / 2, popupPosition.y + 100);

    //set up level visualiser in text
    sf::Text levelText;
    levelText.setFont(font);
    levelText.setCharacterSize(18);
    levelText.setFillColor(sf::Color::White);
    levelText.setStyle(sf::Text::Bold);
    levelText.setPosition(popupPosition + sf::Vector2f(40, 250));
    if (message != "Game Over"){
        levelText.setString("Level: " + std::to_string(levelManager.getCurrentLevel() + 1) );
    }else{
        levelText.setString("Level: " + std::to_string(levelManager.getCurrentLevel()));
    }

    // Loop to handle popup rendering
    bool popupActive = true;
    while (popupActive) {
        sf::Event event;
        while (mainWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                mainWindow.close();
                return;
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (restart.isPressed(mainWindow)) {
                    popupActive = false;
                    levelManager.setTimerLimit(120);
                    
                }
                if (nextLevel.isPressed(mainWindow)) {
                    popupActive = false;
                    levelManager.setTimerLimit(120);
                    levelManager.loadLevel(levelManager.getCurrentLevel() + 1); // Load next level
                    Game game(mainWindow, "NewGame"); // Create a Game object
                    game.run(levelManager, levelManager.getTimerLimit()); // Call the run method to start the game
                }
            }
        }

        // Update stars based on game progress
        int gameStars = levelManager.getGameStars();
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

        // Render popup elements
        mainWindow.clear();
        mainWindow.draw(popupArea);
        scoreBoard.render(mainWindow);
        mainWindow.draw(text);
        mainWindow.draw(levelText);

        if (message == "Lucky Day for You") {
            oneStar.render(mainWindow);
            twoStar.render(mainWindow);
            threeStar.render(mainWindow);
            nextLevel.update(mainWindow);
            nextLevel.render(mainWindow);
        }

        restart.update(mainWindow);
        restart.render(mainWindow);

        mainWindow.display();
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