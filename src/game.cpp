#include "../include/game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>  // For rand()
#include "../include/a_star.h"
#include "../include/settingsPopup.h"
#include "../include/escape.h"
#include "../include/levelManager.h"
#include "../include/winOrLoosePopup.h"

void Game::run(LevelManager& levelManager) {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    // Create a render window
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Mystery Maze");

    // Create an instance of SettingsPopup
    SettingsPopup settingsPopup(window);

    //initialise the Maze width and height
    int mazeWidth = levelManager.getMazeWidth();
    int mazeHeight = levelManager.getMazeHeight();

    // Create a Maze object
    Maze maze(mazeWidth, mazeHeight, 30, 0, 0);
    
    // Create Player and Enemy objects
    Player player(30, sf::Vector2i(rand() % mazeWidth, rand() % mazeHeight));
    Enemy enemy(30, sf::Vector2i(rand() % mazeWidth, rand() % mazeHeight));
    EscapeDoor escapeDoor(30, sf::Vector2i(rand() % mazeWidth, rand() % mazeHeight));

    // Get player, enemy and exit positions
    sf::Vector2i start = enemy.GetEnemyPosition();
    sf::Vector2i goal = player.GetPlayerPosition();
    sf::Vector2i exit = escapeDoor.GetEscapeDoorPosition();

    // Path vector for A* algorithm
    std::vector<sf::Vector2i> path;
    bool pathNeedsUpdate = true; // Flag to control path recalculation

    // Movement cooldowns
    const int PlayerMoveCooldown = 50; // Player cooldown in milliseconds
    sf::Clock PlayerClock;

    const int EnemyMoveCooldown = 150; // Enemy cooldown in milliseconds
    sf::Clock EnemyClock;

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Player movement with cooldown
            if (event.type == sf::Event::KeyPressed) {
                if (PlayerClock.getElapsedTime().asMilliseconds() >= PlayerMoveCooldown) {
                    if (event.key.code == sf::Keyboard::W) player.move(sf::Vector2i(0, -1), maze); // Move up
                    if (event.key.code == sf::Keyboard::S) player.move(sf::Vector2i(0, 1), maze);  // Move down
                    if (event.key.code == sf::Keyboard::A) player.move(sf::Vector2i(-1, 0), maze); // Move left
                    if (event.key.code == sf::Keyboard::D) player.move(sf::Vector2i(1, 0), maze);  // Move right

                    PlayerClock.restart();
                    pathNeedsUpdate = true; // Recalculate path when the player moves
                }
            }
        }

        // Update positions
        start = enemy.GetEnemyPosition(); // Update enemy position
        goal = player.GetPlayerPosition(); // Update player position
        exit = escapeDoor.GetEscapeDoorPosition();

        if (start == goal) {
            std::cout << "Enemy found the Player!" << std::endl;
            
            // Immediately stop the game
            window.clear(sf::Color::Black);
            window.display();
            sf::sleep(sf::milliseconds(100)); // Short pause to allow rendering
            
            window.close(); // Close the game window
            showGameOverPopup(); // Show the "Game Over" popup
            return; // Exit the game loop and end the game
        } else if (goal == exit) {
            std::cout << "Player found the exit!" << std::endl;
            
            // Immediately stop the game
            window.clear(sf::Color::Black);
            window.display();
            sf::sleep(sf::milliseconds(100)); // Short pause to allow rendering
            
            window.close(); // Close the game window
            showLuckyDayPopup(); // Show the "Lucky Day" popup
            return; // Exit the game loop and end the game
        }

        // Update maze
        maze.update();

        // Recalculate the path if needed
        if (pathNeedsUpdate) {
            path.clear();
            start = enemy.GetEnemyPosition(); // Update enemy position
            goal = player.GetPlayerPosition(); // Update player position
            exit = escapeDoor.GetEscapeDoorPosition();
            if (AStar::findPath(maze, start, goal, path, levelManager)) {
                std::cout << "Path found: ";
                for (const auto& step : path) {
                    std::cout << "(" << step.x << ", " << step.y << ") -> ";
                }
                std::cout << "Goal\n";
            } else {
                std::cout << "No path found!\n";
            }

            pathNeedsUpdate = false; // Reset flag
        }

        // Enemy movement with cooldown
        if (maze.getIsGenerated()) { // Ensure the maze is generated
            if (EnemyClock.getElapsedTime().asMilliseconds() >= EnemyMoveCooldown) {
                if (!path.empty()) {
                    sf::Vector2i nextStep = path.front(); // Get next position from A* path
                    enemy.setPosition(nextStep);         // Move enemy
                    path.erase(path.begin());            // Remove step from path
                }
                EnemyClock.restart();
            }
        }

        // Clear window and draw everything
        window.clear(sf::Color::Black);

        maze.draw(window);      // Draw maze
        if (maze.getIsGenerated()) {
            player.draw(window); // Draw player
            enemy.draw(window);  // Draw enemy
            escapeDoor.draw(window); // Draw escape door
        }

        window.display();
    }
}
