#include "../include/star.h"
#include <iostream>
#include <filesystem>
// Constructor
Star::Star(sf::Vector2f position, const std::string& text) {
    // Get the current working directory
    std::string currentDir = std::filesystem::current_path().string();

    // Load textures for idle and active states
    std::string basePath = currentDir + "/assets/Buttons/";
    if (!texIdle.loadFromFile(basePath + text + ".png") ||
        !texActive.loadFromFile(basePath + text + "Active.png")) {
        std::cout << "Error loading star textures!";
        return; // Exit early on error
    }

    // Initialize the texture and position of the star
    starShape.setTexture(texIdle);
    starShape.setPosition(position);
    starShape.setScale(0.2f, 0.2f); // Default scale for stars

    starState = IDLE; // Initial state
}

// Destructor
Star::~Star() {}

// Activate or deactivate the star
void Star::setActive() {
    starState = ACTIVE ;
    starShape.setTexture(texActive);
}

// Check if the star is active
bool Star::isActive() const {
    return starState == ACTIVE;
}

// Render the star
void Star::render(sf::RenderTarget& target) {
    target.draw(starShape);

}

void Star::setScale(const sf::Vector2f& scale) {
    starShape.setScale(scale);
}
