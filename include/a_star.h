#ifndef A_STAR_H
#define A_STAR_H

#include "maze.h" // To use the Maze class
#include "player.h" // To get player position
#include "enemy.h"  // To get enemy position
#include <vector>
#include <queue>
#include <iostream>

class Maze;
// AStarCell: used specifically for pathfinding without conflicting with Maze::Cell
struct AStarCell {
    sf::Vector2i currentPosition;  // Coordinates of the cell
    int g, h;  // g = cost from start, h = heuristic
    AStarCell* parent = nullptr;  // Pointer to the parent cell for path reconstruction

    // Comparator for priority queue (min-heap)
    bool operator<(const AStarCell& other) const {
        return (g + h) > (other.g + other.h); // Min-heap comparison
    }
};

// A* algorithm namespace
namespace AStar {
    static bool isValid(const sf::Vector2i& current, const sf::Vector2i& next, const Maze& maze, const vector<vector<bool>>& visited);
    int heuristic(const sf::Vector2i& a, const sf::Vector2i& b);
    bool findPath(const Maze& maze, const sf::Vector2i& enemyPos, const sf::Vector2i& playerPos, std::vector<sf::Vector2i>& path);
}

#endif // A_STAR_H
