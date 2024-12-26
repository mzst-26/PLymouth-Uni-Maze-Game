#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <vector>

class Enemy {
public:
    // Constructor: Initializes the enemy with a random texture and a start position
    Enemy(int cell_size, sf::Vector2i start_position);

    // Draw the enemy sprite on the window
    void draw(sf::RenderWindow &window);

    // Get the enemy's current position
    sf::Vector2i GetEnemyPosition() const;

    // Set a new position for the enemy
    void setPosition(sf::Vector2i new_position);

private:
    // Position of the enemy in the grid
    sf::Vector2i position;

    // Sprite to represent the enemy
    sf::Sprite sprite;

    // A vector to store all loaded textures
    std::vector<sf::Texture> textures;

    // Load all enemy textures
    void loadTextures();
};

#endif // ENEMY_H
