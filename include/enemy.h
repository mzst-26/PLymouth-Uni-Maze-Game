#ifndef INCLUDE_ENEMY_H_
#define INCLUDE_ENEMY_H_

#include <SFML/Graphics.hpp>
#include <optional>
using namespace std;
// Forward declaration of Maze class
class Maze;

class Enemy {
public:
    Enemy(int cell_size, sf::Vector2i start_position);
    void draw(sf::RenderWindow &window);
    void move( Maze &maze);
    sf::Vector2i getPosition() const { return position; }

private:
    sf::Vector2i position;
    sf::RectangleShape shape;
    optional<sf::Vector2i> choose_next_cell();
};

#endif // INCLUDE_ENEMY_H_