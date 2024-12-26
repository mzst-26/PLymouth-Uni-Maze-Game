#include "../include/enemy.h"
#include <SFML/Graphics.hpp>
#include <cstdlib> // For std::rand() and std::srand()
#include <ctime>   // For std::time()
#include <iostream>

Enemy::Enemy(int cell_size, sf::Vector2i start_position)
    : position(start_position) {
    // Seed the random number generator once
    static bool seedInitialized = false;
    if (!seedInitialized) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        seedInitialized = true;
    }

    // Load the enemy textures
    loadTextures();

    // Choose a random texture from the loaded textures
    int randomIndex = std::rand() % textures.size();
    sprite.setTexture(textures[randomIndex]);

    // Scale the sprite to fit the cell size exactly
    float scaleX = static_cast<float>(cell_size) / sprite.getTexture()->getSize().x;
    float scaleY = static_cast<float>(cell_size) / sprite.getTexture()->getSize().y;
    sprite.setScale(scaleX, scaleY);

    // Center the sprite in the cell
    float centerOffset = (cell_size - (sprite.getGlobalBounds().width)) / 2.f;
    sprite.setPosition(position.x * cell_size + centerOffset, position.y * cell_size + centerOffset);
}

void Enemy::loadTextures() {
    // Define file paths for the 5 enemy textures
    std::vector<std::string> texturePaths = {
        "/Users/mobinzaki/Documents/GitHub/PLymouth-Uni-Maze-Game/assets/Enemy/Enemy1.png",
        "/Users/mobinzaki/Documents/GitHub/PLymouth-Uni-Maze-Game/assets/Enemy/Enemy2.png",
        "/Users/mobinzaki/Documents/GitHub/PLymouth-Uni-Maze-Game/assets/Enemy/Enemy3.png",
        "/Users/mobinzaki/Documents/GitHub/PLymouth-Uni-Maze-Game/assets/Enemy/Enemy4.png",
        "/Users/mobinzaki/Documents/GitHub/PLymouth-Uni-Maze-Game/assets/Enemy/Enemy5.png"
    };

    // Load each texture
    for (const auto& path : texturePaths) {
        sf::Texture texture;
        if (texture.loadFromFile(path)) {
            textures.push_back(texture);
        } else {
            std::cout << "Failed to load texture: " << path << "\n";
        }
    }
}

void Enemy::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

sf::Vector2i Enemy::GetEnemyPosition() const {
    return position;
}

void Enemy::setPosition(sf::Vector2i new_position) {
    position = new_position;

    // Update sprite position to center it in the cell
    float centerOffset = (sprite.getGlobalBounds().width - sprite.getGlobalBounds().height) / 2.f;
    sprite.setPosition(position.x * sprite.getGlobalBounds().width + centerOffset, position.y * sprite.getGlobalBounds().height + centerOffset);
}
