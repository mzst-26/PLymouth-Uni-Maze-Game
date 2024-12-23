#include "../include/home.h"
#include "../include/levelManager.h"
int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed RNG
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Mystery Maze");
    Home mainMenu(window);
    LevelManager levelManager;               // Level manager
    mainMenu.run(levelManager); // Run the main menu
    return 0;
}