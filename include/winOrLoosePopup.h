#ifndef POPUP_WINDOWS_H
#define POPUP_WINDOWS_H

#include <SFML/Graphics.hpp>
#include <string>

// Function to create a popup window
void createWinOrLoosePopupWindow(const std::string& message, const sf::Color& bgColor);

// Function to display the "Game Over" popup
void showGameOverPopup();

// Function to display the "Lucky Day for You" popup
void showLuckyDayPopup();

#endif // POPUP_WINDOWS_H
