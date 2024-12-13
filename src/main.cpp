#include <SFML/Graphics.hpp>
#include "../include/maze.h"

int main() {
    // Create a render window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mystery Maze");

    // Create a Maze object
    Maze maze(24, 14, 30, 0, 0);

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window with black color
        window.clear(sf::Color::Black);

        // Update and draw the maze
        maze.update();         // Call update() on the maze instance
        maze.draw(window);     // Call draw() on the maze instance

        // Display the rendered frame
        window.display();
        //delay for better visualisation of the maze generation algorithm
        sf::sleep(sf::milliseconds(0));
    }

    return 0;
}
