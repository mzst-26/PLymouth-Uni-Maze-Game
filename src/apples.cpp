#include "../include/apples.h"
#include <iostream>


// Define the static texture
sf::Texture Apples::texture;

Apples::Apples(float size, sf::Vector2i position) : position(position) {
    // Load the texture once, if it hasn't been loaded already
    static bool isTextureLoaded = false;
    if (!isTextureLoaded) {
        if (!texture.loadFromFile("/Users/mobinzaki/Documents/GitHub/PLymouth-Uni-Maze-Game/assets/Buttons/Apple.png")) {
            std::cerr << "Error loading texture for apple." << std::endl;
        } else {
            isTextureLoaded = true;
        }
    }

    // Set up the sprite with the shared texture
    sprite.setTexture(texture);
    // Scale the sprite to fit within the cell (assuming cell size is 30)
    sprite.setScale(0.9f, 0.9f); // Adjust scale as needed

    // Center the sprite within the cell
    sf::FloatRect spriteBounds = sprite.getLocalBounds();
    float offsetX = (size - spriteBounds.width * sprite.getScale().x) / 2.0f;
    float offsetY = (size - spriteBounds.height * sprite.getScale().y) / 2.0f;
    sprite.setPosition(static_cast<float>(position.x * size) + offsetX,
                       static_cast<float>(position.y * size) + offsetY);
}



// Method to draw the Apples sprite
void Apples::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

// Getter for Apples position
sf::Vector2i Apples::GetApplesPosition() const {
    return position;
}
