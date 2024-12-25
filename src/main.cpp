#include "../include/home.h"
#include "../include/levelManager.h"

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed RNG

    // Get desktop resolution for full screen
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    // Create a full-screen window
    sf::RenderWindow window(desktopMode, "Mystery Maze", sf::Style::Fullscreen);

    Home mainMenu(window);
    LevelManager levelManager; // Level manager
    mainMenu.run(levelManager); // Run the main menu

    return 0;
}
