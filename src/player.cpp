#include "../include/player.h"
#include "../include/maze.h"
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream> 
#include <vector>
#include <map>
// Constructor: Initializes the player with a given cell size and starting position
Player::Player(int cell_size, sf::Vector2i start_position)
    : position(start_position), cellSize(cell_size), currentFrame(0), animationTime(0.f), animationSpeed(0.2f), lastDirection("down") {
    // Load textures for animations
    loadTextures();

    // Set the initial texture for the sprite (facing down)
    sprite.setTexture(textures["down"][0]);

    // Center the sprite in the cell (cell size = 30)
    float centerOffset = (cell_size - sprite.getGlobalBounds().width) / 2.f;
    sprite.setPosition(position.x * cell_size + centerOffset, position.y * cell_size + centerOffset);

    // Scale the sprite for a better fit
    sprite.setScale(1.1f, 1.1f);
}

// Function: Load textures for all animation frames
void Player::loadTextures() {
    // Define the four movement directions
    std::vector<std::string> directions = {"up", "down", "left", "right"};

    // Load textures for each direction
    for (const auto& dir : directions) {
        for (int i = 1; i <= 3; ++i) { // Assuming 3 frames per direction
            sf::Texture texture;
            // Get the current working directory
            std::string currentDir = std::filesystem::current_path().string();

            // Load the texture from file
            if (texture.loadFromFile(currentDir + "/assets/Player/player_" + dir + std::to_string(i) + ".png")) {
                textures[dir].push_back(texture);
            } else {
                // Log an error if the texture fails to load
                std::cerr << "Failed to load texture: player_" + dir + std::to_string(i) + ".png\n";
            }
        }
    }
}

// Function: Draw the player sprite on the window
void Player::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

// Function: Move the player in a given direction and update its position
void Player::move(sf::Vector2i direction, Maze &maze) {
    // Get the maze grid reference
    auto& grid = maze.getMazeGrid();
    sf::Vector2i newPosition = position + direction;

    // Check if the new position is within bounds and accessible
    if (newPosition.x >= 0 && newPosition.x < grid.size() &&
        newPosition.y >= 0 && newPosition.y < grid[0].size() &&
        canMoveTo(direction, grid)) {
        // Update the player's position
        position = newPosition;

        // Center the sprite in the new cell
        float centerOffset = (cellSize - sprite.getGlobalBounds().width) / 2.f;
        sprite.setPosition(position.x * cellSize + centerOffset, position.y * cellSize + centerOffset);

        // Update the last direction for animation
        lastDirection = getDirectionKey(direction);
    }
}

// Function: Check if the player can move in a specified direction
bool Player::canMoveTo(sf::Vector2i direction, const std::vector<std::vector<Maze::Cell>>& grid) {
    // Get the current cell in the maze
    auto& currentCell = grid[position.x][position.y];

    // Check walls based on the direction
    if (direction.x == -1 && currentCell.left == 1) return false; // Left wall
    if (direction.x == 1 && currentCell.right == 1) return false; // Right wall
    if (direction.y == -1 && currentCell.top == 1) return false; // Top wall
    if (direction.y == 1 && currentCell.bottom == 1) return false; // Bottom wall

    return true; // No walls block the movement
}

// Function: Update the animation of the player (for movement or idle)
void Player::update(float deltaTime) {
    // Increment the animation timer by the elapsed time
    animationTime += deltaTime;

    // If the timer exceeds the animation speed, update the frame
    if (animationTime >= animationSpeed) {
        animationTime = 0.f; // Reset the timer
        currentFrame = (currentFrame + 1) % textures[lastDirection].size(); // Cycle through frames
        sprite.setTexture(textures[lastDirection][currentFrame]); // Set the new frame
    }
}

// Function: Get the key for the direction (e.g., "up", "down", "left", "right")
std::string Player::getDirectionKey(sf::Vector2i direction) {
    if (direction == sf::Vector2i(0, -1)) return "up";
    if (direction == sf::Vector2i(0, 1)) return "down";
    if (direction == sf::Vector2i(-1, 0)) return "left";
    if (direction == sf::Vector2i(1, 0)) return "right";
    return lastDirection; // Return the last direction if no movement
}
