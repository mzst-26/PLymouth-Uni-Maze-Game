#include "../include/maze.h" // Include the header file
#include <cstdlib> // For rand()
#include <optional> // For std::optional
#include <vector> // For std::vector
#include <stack> // For std::stack

using namespace std;

// Constructor for the Maze class
Maze::Maze(int width, int height, int cell_size, int starting_point_X, int starting_point_Y)
    : maze_width{width}, maze_height{height}, cell_size{cell_size}, 
      current_position{starting_point_X, starting_point_Y}, 
      maze_grid(width, vector<Maze::Cell>(height)), 
      is_generated{false}, is_wallsRemoved{false} { // Initialize is_generated

    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    // Get the coordinates of the current cell
    current_cell = &maze_grid[current_position.x][current_position.y];
    // Define it as visited
    current_cell->visited = true;
    // Push the current position to the backtracking stack for when hitting a dead end
    backtracking_stack.push(current_position);

}


// Function to choose the next cell to visit
optional<sf::Vector2i> Maze::choose_next_cell() {
    vector<sf::Vector2i> list_of_next_cells;

    // Check for unvisited neighbors
    if (current_position.x > 0 && !maze_grid[current_position.x - 1][current_position.y].visited)
        list_of_next_cells.push_back({current_position.x - 1, current_position.y});
    if (current_position.x < maze_width - 1 && !maze_grid[current_position.x + 1][current_position.y].visited)
        list_of_next_cells.push_back({current_position.x + 1, current_position.y});
    if (current_position.y > 0 && !maze_grid[current_position.x][current_position.y - 1].visited)
        list_of_next_cells.push_back({current_position.x, current_position.y - 1});
    if (current_position.y < maze_height - 1 && !maze_grid[current_position.x][current_position.y + 1].visited)
        list_of_next_cells.push_back({current_position.x, current_position.y + 1 });

    // Choose a random cell from the list
    if (!list_of_next_cells.empty()) {
        int index = rand() % list_of_next_cells.size();
        return list_of_next_cells[index];
    }
    return nullopt;
}
const std::vector<std::vector<Maze::Cell>>& Maze::getMazeGrid() const {
    return maze_grid; 
}

bool Maze::allCellsVisited() {
    for (int x = 0; x < maze_width; ++x) {
        for (int y = 0; y < maze_height; ++y) {
            if (!maze_grid[x][y].visited) {
                return false; // Found an unvisited cell
            }
        }
    }
    return true; // All cells are visited
}

// Function to generate the maze
void Maze::generate() {
    auto next_position = choose_next_cell();
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
            current_cell->bottom = false;
            next_cell->top = false;
        }
        if (current_position.y > next.y) {
            current_cell->top = false;
            next_cell->bottom = false;
        }

        // Update the current position and cell
        current_position = next;
        current_cell = next_cell;
        backtracking_stack.push(current_position);
    } else if (!backtracking_stack.empty()) {
        // Backtrack if no unvisited neighbors
        current_position = backtracking_stack.top();
        current_cell = &maze_grid[current_position.x][current_position.y];
        backtracking_stack.pop();
    }
        // Check if the maze is fully generated
    if (allCellsVisited()) {
        is_generated = true;
    }
}

// Function to update the maze generation
void Maze::update() {
    if (!is_generated) {
        generate();
    }
}

// Function to check if the maze is generated
bool Maze::getIsGenerated() {
    return is_generated;
}
bool Maze::isWallsRemoved(){
     return is_wallsRemoved;
}
// Function to draw the maze using SFML
void Maze::draw(sf::RenderWindow &window) {
    for (int y = 0; y < maze_height; y++) {
        for (int x = 0; x < maze_width; x++) {
            int gx = x * cell_size;
            int gy = y * cell_size;
            Cell* cell = &maze_grid[x][y];

            // Draw walls
            if (cell->top) {
                sf::RectangleShape line(sf::Vector2f(cell_size, 1));
                line.setFillColor(sf::Color::Blue);
                line.setPosition(gx, gy);
                window.draw(line);
            }
            if (cell->bottom) {
                sf::RectangleShape line(sf::Vector2f(cell_size, 1));
                line.setFillColor(sf::Color::Blue);
                line.setPosition(gx, gy + cell_size - 1);
                window.draw(line);
            }
            if (cell->left) {
                sf::RectangleShape line(sf::Vector2f(1, cell_size));
                line.setFillColor(sf::Color::Blue);
                line.setPosition(gx, gy);
                window.draw(line);
            }
            if (cell->right) {
                sf::RectangleShape line(sf::Vector2f(1, cell_size));
                line.setFillColor(sf::Color::Blue);
                line.setPosition(gx + cell_size - 1, gy);
                window.draw(line);
            }
        }
    }

    
}


void Maze::removeRandomWalls(int numWallsToRemove) {
    int wallsRemoved = 0;
    is_wallsRemoved = true;
    while (wallsRemoved < numWallsToRemove) {
        // Randomly select a cell
        int x = rand() % maze_width;
        int y = rand() % maze_height;

        // Randomly choose a direction to remove a wall (0: top, 1: bottom, 2: left, 3: right)
        int direction = rand() % 4;

        // Determine the neighboring cell based on the chosen direction
        int nx = x, ny = y;

        switch (direction) {
            case 0: ny -= 1; break; // Top
            case 1: ny += 1; break; // Bottom
            case 2: nx -= 1; break; // Left
            case 3: nx += 1; break; // Right
        }

        // Ensure the neighbor is within bounds
        if (nx >= 0 && nx < maze_width && ny >= 0 && ny < maze_height) {
            // Remove the wall between the current cell and the neighboring cell
            if (direction == 0 && maze_grid[x][y].top) { // Top wall
                maze_grid[x][y].top = false;
                maze_grid[nx][ny].bottom = false;
                wallsRemoved++;
            } else if (direction == 1 && maze_grid[x][y].bottom) { // Bottom wall
                maze_grid[x][y].bottom = false;
                maze_grid[nx][ny].top = false;
                wallsRemoved++;
            } else if (direction == 2 && maze_grid[x][y].left) { // Left wall
                maze_grid[x][y].left = false;
                maze_grid[nx][ny].right = false;
                wallsRemoved++;
            } else if (direction == 3 && maze_grid[x][y].right) { // Right wall
                maze_grid[x][y].right = false;
                maze_grid[nx][ny].left = false;
                wallsRemoved++;
            }
        }
    }
}
