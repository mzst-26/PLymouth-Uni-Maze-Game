#include "../include/maze.h" //include the header file
using namespace std;
//first step is to initialise the maze and set up the headers for it in maze.h
Maze::Maze(int width, int height, int cell_size int starting_point_X int starting_point_Y)
:maze_width{width}, maze_height{height}, cell_size{cell_size}, current_position{starting_point_X, starting_point_Y}, maze_grid{width, vector<Cell>height}{
//get the coordinates of the current cell
current_cell = maze_grid[current_position.x, current_position.y]
//define it as visited
current_cell->visited = true
//push the current position to the backtracking stack for when hitting a dead end
backtracking_stack.push(current_position)
}
