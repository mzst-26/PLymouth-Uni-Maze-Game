#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "maze.h"
#include <map>
#include <vector>
#include <string>

class Player {
public:
    // Constructor
    Player(int cell_size, sf::Vector2i start_position);

    // Draw the player
    void draw(sf::RenderWindow &window);

    // Move the player
    void move(sf::Vector2i direction, Maze &maze);

    // Update the player (for animations)
    void update(float deltaTime);

    // Get the player's current position
    sf::Vector2i GetPlayerPosition() const { return position; };

private:
    // Position of the player in the maze grid
    sf::Vector2i position;

    // Size of each cell in the maze
    int cellSize;

    // Sprite to represent the player
    sf::Sprite sprite;

    // Textures for animation frames
    std::map<std::string, std::vector<sf::Texture>> textures;

    // Current animation frame
    int currentFrame;

    // Timer for animation
    float animationTime;

    // Speed of animation (time between frames)
    float animationSpeed;

    // Last movement direction (for idle animations)
    std::string lastDirection;

    // Load textures for animation
    void loadTextures();

    // Check if the player can move to the specified direction
    bool canMoveTo(sf::Vector2i direction, const std::vector<std::vector<Maze::Cell>>& grid);

    // Update the player's animation based on the last direction
    void updateAnimation(sf::Vector2i direction);

    // Get the key for the direction (e.g., "up", "down", "left", "right")
    std::string getDirectionKey(sf::Vector2i direction);
};

#endif // PLAYER_H
