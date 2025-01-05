#include "../include/a_star.h"
#include <cmath>        // For absolute value calculations in the heuristic
#include <algorithm>    // For std::reverse to reverse the path order

using namespace std;

// Function to calculate the Manhattan distance heuristic
// This estimates the cost from point 'a' to point 'b'
int AStar::heuristic(const sf::Vector2i& a, const sf::Vector2i& b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y); // Manhattan distance formula
}

// Function to check if a given cell is valid for traversal
bool AStar::isValid(const sf::Vector2i& current, const sf::Vector2i& next, 
                    const Maze& maze, const vector<vector<bool>>& visited, 
                    LevelManager& levelManager) {
    // Get the dimensions of the maze from the level manager
    int mazeWidth = levelManager.getMazeWidth();
    int mazeHeight = levelManager.getMazeHeight();

    // Check if the 'next' cell is within bounds and not already visited
    if (next.x < 0 || next.y < 0 || next.x >= mazeWidth || next.y >= mazeHeight || visited[next.x][next.y]) 
        return false;

    // Access the maze grid and current cell's wall data
    const auto& grid = maze.getMazeGrid();
    const auto& currentCell = grid[current.x][current.y];

    // Check if moving to 'next' would hit a wall
    if (next.x == current.x - 1 && currentCell.left) return false;  // Moving left
    if (next.x == current.x + 1 && currentCell.right) return false; // Moving right
    if (next.y == current.y - 1 && currentCell.top) return false;   // Moving up
    if (next.y == current.y + 1 && currentCell.bottom) return false;// Moving down

    // If all checks pass, the cell is valid
    return true;
}

// Main A* pathfinding function
bool AStar::findPath(const Maze& maze, const sf::Vector2i& start, const sf::Vector2i& goal, 
                     vector<sf::Vector2i>& path, LevelManager& levelManager) {
    // Priority queue to store open cells (sorted by their total cost f = g + h)
    priority_queue<AStarCell> openList;

    //// Get maze dimensions
    int mazeWidth = levelManager.getMazeWidth();
    int mazeHeight = levelManager.getMazeHeight();

    /// Create a 2D visited array to track explored cells
    vector<vector<bool>> visited(mazeWidth, vector<bool>(mazeHeight, false));
    
    /// Initialize the starting cell with g=0 and h=heuristic to the goal
    AStarCell startCell = {start, 0, heuristic(start, goal), nullptr};
    openList.push(startCell); // Add start cell to the open list

    //// Direction vectors for exploring neighbors (left, right, up, down)
    vector<int> dx = {-1, 1, 0, 0}; 
    vector<int> dy = {0, 0, -1, 1};

    // While there are cells in the open list
    while (!openList.empty()) {
        // Get the cell with the lowest f-value from the queue
        AStarCell current = openList.top();
        openList.pop();

        // Check if we have reached the goal
        if (current.currentPosition == goal) {
            // Reconstruct the path by backtracking from the goal to the start
            AStarCell* cell = &current;
            while (cell != nullptr) {
                path.push_back(cell->currentPosition); // Add the cell to the path
                cell = cell->parent;                  // Move to the parent cell
            }
            reverse(path.begin(), path.end());        // Reverse path to go from start to goal
            return true;                              // Path found
        }

        // Mark the current cell as visited
        visited[current.currentPosition.x][current.currentPosition.y] = true;

        // Explore all four neighboring cells
        for (int i = 0; i < 4; ++i) {
            // Compute the position of the neighboring cell
            sf::Vector2i next = {current.currentPosition.x + dx[i], current.currentPosition.y + dy[i]};

            // Check if the neighbor is valid for traversal
            if (isValid(current.currentPosition, next, maze, visited, levelManager)) {
                // Create a new AStarCell for the neighbor
                AStarCell neighbor = {
                    next,                          // Position of the neighbor
                    current.g + 1,                // g-value: cost to move to this neighbor
                    heuristic(next, goal),        // h-value: estimated cost to goal
                    new AStarCell(current)        // Parent pointer (for path reconstruction)
                };
                // Add the neighbor to the open list for further exploration
                openList.push(neighbor);
            }
        }
    }

    // If the open list is empty and the goal was not reached, no path exists
    return false;
}
