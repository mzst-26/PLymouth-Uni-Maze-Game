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

//second we find unvisited cells around the current cell
optional<sf::Vector2i> Maze::choose_next_cell() {
    //An array that holds all valid possible next moves
    vector<sf::Vector2i> list_of_next_cells;
    
    // Add valid neighbors to the list
    //checking for if the next_cell is going out of bound or not and if it is visited/ not visited
    if (current_position.x > 0 && !maze_grid[current_position.x - 1][current_position.y].visited)
        list_of_next_cells.push_back({current_position.x - 1, current_position.y});
    if (current_position.x < maze_width - 1 && !maze_grid[current_position.x + 1][current_position.y].visited)
        list_of_next_cells.push_back({current_position.x + 1, current_position.y});
    if (current_position.y > 0 && !maze_grid[current_position.x][current_position.y - 1].visited)
        list_of_next_cells.push_back({current_position.x, current_position.y - 1});
    if (current_position.y < maze_height - 1 && !maze_grid[current_position.x][current_position.y + 1].visited)
        list_of_next_cells.push_back({current_position.x, current_position.y + 1});

    //chosing a random one unless the stack is empty(end of maze generation)
    if (!list_of_next_cells.empty()) {
        int index = rand() % list_of_next_cells.size();
        return list_of_next_cells[index];
    }
    return nullopt;
}


// step is to generate the maze
void Maze::generate() {
    auto next_position = choose_next_cell();
    // If there are unvisited cells around the current cell, continue generating
    if (next_position) {

        // Move to the next cell
        sf::Vector2i next = *next_position;
        Cell* next_cell = &maze_grid[next.x][next.y];
        next_cell->visited = true;

        // Remove walls between current and next cell
        if (current_position.x < next.x) {
            current_cell->right = false;
            next_cell->left = false;
        }
        if (current_position.x > next.x) {
            current_cell->left = false;
            next_cell->right = false;
        }
        if (current_position.y < next.y) {
            current_cell->botton = false;
            next_cell->top = false;
        }
        if (current_position.y > next.y) {
            current_cell->top = false;
            next_cell->botton = false;
        }

        // update the current position/cell and set it to current position/cell is now next position/cell
        current_position = next;
        current_cell = next_cell;
        // push the current position to the backtracking stack for when hitting a dead end
        backtracking_stack.push(current_position);

    } else if (!backtracking_stack.empty()) {
        // Backtrack if no unvisited neighbors
        current_position = backtracking_stack.top();
        current_cell = &maze_grid[current_position.x][current_position.y];
        backtracking_stack.pop();
    }
}

//Check if the maze ic complete and generated if not continue
void Maze::update() {
    if (!is_generated) generate();
}




