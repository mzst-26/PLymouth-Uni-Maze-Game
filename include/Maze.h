#ifndef INCLUDE_MAZE_H_ // Header guards prevent the multiple inclusion of a header file
#define INCLUDE_MAZE_H_

#include <stack> 
#include <vector>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <SFML/Graphics.hpp>

// Forward declaration of Player class
class Player;

using namespace std;

class Maze {
public:
    // Declare the type of Maze function and its parameters 
    Maze(int width, int height, int cell_size, int starting_point_X, int starting_point_Y);
    
    void update();
    void draw(sf::RenderWindow &window);
    bool getIsGenerated();
    bool allCellsVisited();
    sf::Vector2i getCurrentPosition() const; // Method to get the current position

    // Define the type of Cell object and its properties with their default values
    struct Cell {
        bool visited{false};
        bool top{true};
        bool bottom{true};
        bool left{true};
        bool right{true};      
    };

    vector<vector<Cell>>& getMazeGrid(); // Method to get the maze grid

private:
    vector<vector<Cell>> maze_grid; // Declare maze_grid here

    int maze_width;
    int maze_height;
    int cell_size;
    sf::Vector2i current_position{0, 0};
    Cell *current_cell{nullptr};
    stack<sf::Vector2i> backtracking_stack;
    void generate();
    bool is_generated{false};
    
    optional<sf::Vector2i> choose_next_cell();
};

#endif // INCLUDE_MAZE_H_