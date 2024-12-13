#include <stack> 
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;

class Maze{
    public:
        //declare the type of Maze function and it's parameters 
        Maze(int width, int height, int cell_size, int starting_point_X, int starting_point_Y);
    private:
        //define the type of Cell opject and it's properties with their default values
        struct Cell{
            bool visited{false};
            bool top{true};
            bool bottom{true};
            bool left{true};
            bool right{true};      
            
        };
        //define the type of other Maze variables and parameters 
        int maze_width;
        int maze_height;
        int cell_size;
        

        //2D array type of the current position
        sf::Vector2i current_position{0, 0};
        vector<vector<Cell>> maze_grid;
        Cell *current_cell{nullptr};
        stack<sf::Vector2i> backtracking_stack;

};