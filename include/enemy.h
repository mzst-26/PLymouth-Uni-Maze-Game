#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <vector>

class Enemy {
public:
    // Constructor
    Enemy(int cell_size, sf::Vector2i start_position);

    // Draw the enemy
    void draw(sf::RenderWindow &window);

    // Get the enemy's position
    sf::Vector2i GetEnemyPosition() const;

    // Set a new position for the enemy (only if not stopped)
    void setPosition(sf::Vector2i new_position);

    // Stop the enemy from moving
    void stop();

    // Resume enemy movement
    void resume();

private:
    sf::Vector2i position;             // Current position
    sf::Sprite sprite;                 // Enemy sprite
    std::vector<sf::Texture> textures; // Enemy textures
    bool stopped = false;              // Movement status flag

    // Load textures for the enemy
    void loadTextures();
};

#endif // ENEMY_H
