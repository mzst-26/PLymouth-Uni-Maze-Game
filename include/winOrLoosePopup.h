#ifndef POPUP_WINDOWS_H
#define POPUP_WINDOWS_H

#include <SFML/Graphics.hpp>
#include "levelManager.h"
#include <string>

// Function to create a popup window
class WinOrLoose{
    public:
    void createWinOrLoosePopupWindow(const std::string& message, const sf::Color& bgColor, LevelManager& levelManager, sf::RenderWindow& window);

    // Function to display the "Game Over" popup
    void showGameOverPopup(LevelManager& levelManager, sf::RenderWindow& window);

    // Function to display the "Lucky Day for You" popup
    void showLuckyDayPopup(LevelManager& levelManager, sf::RenderWindow& window);

    private:


};
#endif // POPUP_WINDOWS_H
