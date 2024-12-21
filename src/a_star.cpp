#include "../include/a_star.h"
#include <cmath>
#include <algorithm> // For std::reverse

using namespace std;

// Manhattan distance heuristic (a way of estimating the shortest path between two points)
int AStar::heuristic(const sf::Vector2i& a, const sf::Vector2i& b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y); // Manhattan distance
}

// Check if a cell is valid (not visited and navigable)
bool AStar::isValid(const sf::Vector2i& current, const sf::Vector2i& next, const Maze& maze, const vector<vector<bool>>& visited, LevelManager& levelManager) {
    //initialise the Maze width and height
    int mazeWidth = levelManager.getMazeWidth();
    int mazeHeight = levelManager.getMazeHeight();
     // Check if next cell is within bounds and not already visited
    if (next.x < 0 || next.y < 0 || next.x >= mazeWidth || next.y >= mazeHeight || visited[next.x][next.y]) 
        return false;

    const auto& grid = maze.getMazeGrid();
    const auto& currentCell = grid[current.x][current.y];

    // Check walls based on movement direction
    if (next.x == current.x - 1 && currentCell.left) return false;  // Moving left into a wall
    if (next.x == current.x + 1 && currentCell.right) return false; // Moving right into a wall
    if (next.y == current.y - 1 && currentCell.top) return false;   // Moving up into a wall
    if (next.y == current.y + 1 && currentCell.bottom) return false;// Moving down into a wall

    return true; // The move is valid
}


// A* pathfinding algorithm
bool AStar::findPath(const Maze& maze, const sf::Vector2i& start, const sf::Vector2i& goal, vector<sf::Vector2i>& path, LevelManager& levelManager ) {
    priority_queue<AStarCell> openList; // Priority queue for open cells
    //initialise the maze width and height
    int mazeWidth = levelManager.getMazeWidth();
    int mazeHeight = levelManager.getMazeHeight();
    vector<vector<bool>> visited(mazeWidth, vector<bool>(14, false));
    // Initialize start cell
    AStarCell startCell = {start, 0, heuristic(start, goal), nullptr};
    openList.push(startCell);

    vector<int> dx = {-1, 1, 0, 0}; // Neighbor offsets: left, right, up, down
    vector<int> dy = {0, 0, -1, 1};

    while (!openList.empty()) {
        AStarCell current = openList.top();
        openList.pop();

        // If we've reached the goal
        if (current.currentPosition == goal) {
            AStarCell* cell = &current;
            while (cell != nullptr) {
                path.push_back(cell->currentPosition);
                cell = cell->parent;
            }
            reverse(path.begin(), path.end()); // Start to goal
            return true;
        }

        // Mark current cell as visited
        visited[current.currentPosition.x][current.currentPosition.y] = true;

        // Explore neighbors
       for (int i = 0; i < 4; ++i) {
            sf::Vector2i next = {current.currentPosition.x + dx[i], current.currentPosition.y + dy[i]};

            if (isValid(current.currentPosition, next, maze, visited, levelManager)) {
                AStarCell neighbor = {next, current.g + 1, heuristic(next, goal), new AStarCell(current)};
                openList.push(neighbor);
            }
        }
    }
    // No path found
    return false;
}
