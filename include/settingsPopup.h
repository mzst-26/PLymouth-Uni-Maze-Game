#ifndef SETTINGS_POPUP_H
#define SETTINGS_POPUP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "button.h"
#include "levelManager.h"

class LevelManager;

class SettingsPopup {
public:
    SettingsPopup(sf::RenderWindow& window);
    void render();
    void handleInput(const sf::Event& event, LevelManager& levelManager);
    std::string getCurrentDifficulty() const;

private:
    sf::RenderWindow& window;

    Button easyButton;
    Button mediumButton;
    Button hardButton;

    int activeButtonIndex;
    std::string currentDifficulty;
    sf::Font titleFont;
    sf::Text titleText;
};

#endif // SETTINGS_POPUP_H