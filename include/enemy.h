#ifndef INCLUDE_ENEMY_H_
#define INCLUDE_ENEMY_H_

#include <SFML/Graphics.hpp>

class Enemy {
public:
    // Constructor to initialize the enemy with a cell size and starting position
    Enemy(int cell_size, sf::Vector2i start_position);

    // Function to draw the enemy on the window
    void draw(sf::RenderWindow &window);

    // Getter for the enemy's current position
    sf::Vector2i GetEnemyPosition() const;

    // Setter to update the enemy's position
    void setPosition(sf::Vector2i new_position);

private:
    sf::Vector2i position;      // Current position of the enemy
    sf::RectangleShape shape;   // Graphical representation of the enemy
};

#endif // INCLUDE_ENEMY_H_
