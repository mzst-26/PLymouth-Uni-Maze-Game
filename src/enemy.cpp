#include "../include/enemy.h"
#include "../include/maze.h"
#include <iostream> 
#include <SFML/Graphics.hpp>
#include <optional> // Include for std::optional
#include <vector>   // Include for std::vector

using namespace std;

Enemy::Enemy(int cell_size, sf::Vector2i start_position)
    : position(start_position) {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    shape.setSize(sf::Vector2f(cell_size, cell_size)); // Set size of the enemy
    shape.setFillColor(sf::Color::Red); // Color of the enemy
    shape.setPosition(position.x * cell_size + 2.5f, position.y * cell_size + 2.5f); // Center the enemy in the cell
    shape.setScale(0.90, 0.90);
}

void Enemy::draw(sf::RenderWindow &window) {
    window.draw(shape);
}

void Enemy::move(Maze &maze) {
    auto next_position = choose_next_cell(); // Get the next position
    if (!next_position) {
        cout << "No valid next position found!" << endl;
        return; // No valid move available
    }

    auto& grid = maze.getMazeGrid(); // Get a reference to the maze grid
    sf::Vector2i newPosition = *next_position; // Dereference the optional to get the new position

    // Ensure the new position is within bounds
    if (newPosition.x >= 0 && newPosition.x < grid.size() && newPosition.y >= 0 && newPosition.y < grid[0].size()) {
        auto& currentCell = grid[position.x][position.y]; // Current cell
        auto& nextCell = grid[newPosition.x][newPosition.y]; // Next cell

        // Check if the next cell is a wall
        if (newPosition.x == position.x - 1 && currentCell.left == 1) {
            cout << "Wall on the left" << endl;
            return; // Can't move left
        }
        if (newPosition.x == position.x + 1 && currentCell.right == 1) {
            cout << "Wall on the right" << endl;
            return; // Can't move right
        }
        if (newPosition.y == position.y - 1 && currentCell.top == 1) {
            cout << "Wall on the top" << endl;
            return; // Can't move up
        }
        if (newPosition.y == position.y + 1 && currentCell.bottom == 1) {
            cout << "Wall on the bottom" << endl;
            return; // Can't move down
        }

        // Move the enemy to the new position
        position = newPosition;
        shape.setPosition(position.x * shape.getSize().x + 2.5f, position.y * shape.getSize().y + 2.5f);
        cout << "New Position: (" << position.x << ", " << position.y << ")" << endl;
    } else {
        cout << "New position out of bounds!" << endl;
    }
}

optional<sf::Vector2i> Enemy::choose_next_cell() {
    vector<sf::Vector2i> list_of_next_cells;

    // Check for unvisited neighbors (or any other logic you want for enemy movement)
    // This logic can be similar to the one in the Maze class
    if (position.x > 0) list_of_next_cells.push_back({position.x - 1, position.y}); // Left
    if (position.x < 24 - 1) list_of_next_cells.push_back({position.x + 1, position.y}); // Right
    if (position.y > 0) list_of_next_cells.push_back({position.x, position.y - 1}); // Up
    if (position.y < 14 - 1) list_of_next_cells.push_back({position.x, position.y + 1}); // Down

    // Choose a random cell from the list
    if (!list_of_next_cells.empty()) {
        int index = rand() % list_of_next_cells.size();
        return list_of_next_cells[index];
    }
    return nullopt;
}