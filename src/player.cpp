#include "../include/player.h"
#include "../include/maze.h"
#include <iostream> 
#include <SFML/Graphics.hpp>
using namespace std;

Player::Player(int cell_size, sf::Vector2i start_position)
    : position(start_position) {
    shape.setSize(sf::Vector2f(cell_size, cell_size)); // Slightly smaller than the cell
    shape.setFillColor(sf::Color::Green); // Color of the player
    shape.setPosition(position.x * cell_size + 2.5f, position.y * cell_size + 2.5f); // Center the player in the cell
    shape.setScale(0.90, 0.90);
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(shape);
}

void Player::move(sf::Vector2i direction, Maze &maze) {
    auto& grid = maze.getMazeGrid(); // Get a reference to the maze grid

    // Ensure the new position is within bounds
    sf::Vector2i newPosition = position + direction;

    // Check if the new position is within the bounds of the maze
    if (newPosition.x >= 0 && newPosition.x < grid.size() && newPosition.y >= 0 && newPosition.y < grid[0].size()) {
        auto& currentCell = grid[position.x][position.y]; // Current cell
        auto& nextCell = grid[newPosition.x][newPosition.y]; // Next cell

    // for debugging
        // cout << "Current Cell: ("
        //      << position.x << ", " << position.y << ") - "
        //      << "Top: " << currentCell.top << ", "
        //      << "Bottom: " << currentCell.bottom << ", "
        //      << "Left: " << currentCell.left << ", "
        //      << "Right: " << currentCell.right << endl;

        //Check if the next cell is a wall
        if (direction.x == -1 && currentCell.left == 1) {
            cout << "Wall on the left" << endl;
            return; // Can't move left
        }
        if (direction.x == 1 && currentCell.right == 1) {
            cout << "Wall on the right" << endl;
            return; // Can't move right
        }
        if (direction.y == -1 && currentCell.top == 1) {
            cout << "Wall on the top" << endl;
            return; // Can't move up
        }
        if (direction.y == 1 && currentCell.bottom == 1) {
            cout << "Wall on the bottom" << endl;
            return; // Can't move down
        }

        // Move the player to the new position
        position = newPosition;
        shape.setPosition(position.x * shape.getSize().x + 2.5f, position.y * shape.getSize().y + 2.5f);
        cout << "New Position: (" << position.x << ", " << position.y << ")" << endl;
    } else {
        cout << "New position out of bounds!" << endl;
    }
}