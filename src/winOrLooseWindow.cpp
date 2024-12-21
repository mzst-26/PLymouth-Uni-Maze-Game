#include <SFML/Graphics.hpp>
#include <string>
#include "../include/winOrLoosePopup.h"

// Function to create a popup window
void createWinOrLoosePopupWindow(const std::string& message, const sf::Color& bgColor) {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(400, 200), "Popup", sf::Style::Titlebar | sf::Style::Close);

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
        }

        // Clear and redraw
        window.clear(bgColor);
        window.draw(text);
        window.display();
    }
}

// Function to display the "Game Over" popup
void showGameOverPopup() {
    createWinOrLoosePopupWindow("Game Over", sf::Color::Red);
}

// Function to display the "Lucky Day for You" popup
void showLuckyDayPopup() {
    createWinOrLoosePopupWindow("Lucky Day for You", sf::Color::Green);
}