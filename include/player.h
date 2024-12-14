#ifndef INCLUDE_PLAYER_H_
#define INCLUDE_PLAYER_H_

#include <SFML/Graphics.hpp>

// Forward declaration of Maze class
class Maze;

class Player {
public:
    Player(int cell_size, sf::Vector2i start_position);
    void draw(sf::RenderWindow &window);
    void move(sf::Vector2i direction, Maze &maze);
    sf::Vector2i getPosition() const { return position; }

private:
    sf::Vector2i position;
    sf::RectangleShape shape;
};

#endif // INCLUDE_PLAYER_H_