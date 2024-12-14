#include <SFML/Graphics.hpp>
#include "../include/maze.h"
#include "../include/player.h"
#include "../include/enemy.h"
#include <iostream> // Include for std::cout
#include <cstdlib>  // Include for rand()

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    // Create a render window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mystery Maze");

    // Create a Maze object
    Maze maze(24, 14, 30, 0, 0);
    
    // Create a Player object after maze generation
    Player player(30, sf::Vector2i(rand() % 24, rand() % 14));

 // Create a Player object after maze generation
    Enemy enemy(30, sf::Vector2i(rand() % 24, rand() % 14));

    // Cooldown time in milliseconds
    const int PlayerMoveCooldown = 50; // 50 milliseconds
    sf::Clock PlayerClock; // Clock to track time 
    
     const int EnemyMoveCooldown = 100; // 100 milliseconds
     sf::Clock EnemyClock; // Clock to track time 
    
    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Check for key presses to move the player
            if (event.type == sf::Event::KeyPressed) {
                // Check if enough time has passed since the last move
                if (PlayerClock.getElapsedTime().asMilliseconds() >= PlayerMoveCooldown) {
                    if (event.key.code == sf::Keyboard::W) {
                        // std::cout << "Up key pressed" << std::endl; 
                        // Debug output
                        player.move(sf::Vector2i(0, -1), maze); // Move up
                    }
                    if (event.key.code == sf::Keyboard::S) {
                        // std::cout << "Down key pressed" << std::endl; 
                        // Debug output
                        player.move(sf::Vector2i(0, 1), maze); // Move down
                    }
                    if (event.key.code == sf::Keyboard::A) {
                        // std::cout << "Left key pressed" << std::endl; // Debug output
                        player.move(sf::Vector2i(-1, 0), maze); // Move left
                    }
                    if (event.key.code == sf::Keyboard::D) {
                        // std::cout << "Right key pressed" << std::endl; // Debug output
                        player.move(sf::Vector2i(1, 0), maze); // Move right
                    }
                    // Reset the PlayerClock after a move
                    PlayerClock.restart();
                }
            }
        }

        // Update the maze generation
        maze.update();

        // Clear the window with black color
        window.clear(sf::Color::Black);

        // Draw the maze
        maze.draw(window); 

        //check if the maze is fully generated
        if (maze.getIsGenerated()){
             player.draw(window); // Draw the player
             enemy.draw(window);
             if (EnemyClock.getElapsedTime().asMilliseconds() >= EnemyMoveCooldown) {
             enemy.move(maze);
             EnemyClock.restart();
             }
          

        }
   
        // Display the rendered frame
        window.display();
    }

    return 0;
}