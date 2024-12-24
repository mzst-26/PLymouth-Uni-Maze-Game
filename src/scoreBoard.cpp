#include "../include/scoreBoard.h"
#include <iostream>

// Constructor
ScoreBoard::ScoreBoard(sf::Vector2f position, const std::string& fileName, const std::string& text) {
    // Load textures for idle and active states
    std::string basePath = "/Users/mobinzaki/Documents/GitHub/PLymouth-Uni-Maze-Game/assets/Buttons/";
    if (!texIdle.loadFromFile(basePath + fileName + ".png") ||
        !texActive.loadFromFile(basePath + fileName + "HOP.png")) {
        std::cerr << "Error loading star textures!" << std::endl;
        return; // Exit early on error
    }

    // Initialize the texture and position of the star
    starShape.setTexture(texIdle);
    starShape.setPosition(position);
    starShape.setScale(0.8f, 0.8f); // Default scale for stars

    // Load the font and handle errors
    try {
        if (!font.loadFromFile("/Users/mobinzaki/Documents/GitHub/PLymouth-Uni-Maze-Game/assets/fonts/font.ttf")) {
            throw std::runtime_error("Error loading font!");
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return; // Exit early on error
    }

    // Set up the fixed label ("Your Reward")
    rewardLabel.setFont(font);
    rewardLabel.setString("Your Reward");
    rewardLabel.setCharacterSize(24);
    rewardLabel.setFillColor(sf::Color::Black);
    rewardLabel.setPosition(
        position.x + (starShape.getGlobalBounds().width - rewardLabel.getGlobalBounds().width) / 2,
        position.y + 20 // Adjust top margin
    );

    // Set up the dynamic reward text
    rewardAmount.setFont(font);
    rewardAmount.setString(text); // Dynamic reward amount
    rewardAmount.setCharacterSize(24);
    rewardAmount.setFillColor(sf::Color::Black);
    rewardAmount.setPosition(
        position.x + (starShape.getGlobalBounds().width - rewardAmount.getGlobalBounds().width) / 2,
        rewardLabel.getPosition().y + rewardLabel.getGlobalBounds().height + 10 // Adjust below the label
    );

    starState = IDLE; // Initial state
}

// Destructor
ScoreBoard::~ScoreBoard() {};

// Render the star and text
void ScoreBoard::render(sf::RenderTarget& target) {
    target.draw(starShape);
    target.draw(rewardLabel);  // Draw the fixed label
    target.draw(rewardAmount); // Draw the dynamic reward amount
}

// Update the reward amount text
void ScoreBoard::updateRewardAmount(const std::string& amount) {
    rewardAmount.setString(amount); // Update the text
    // Re-center the dynamic text
    rewardAmount.setPosition(
        starShape.getPosition().x + (starShape.getGlobalBounds().width - rewardAmount.getGlobalBounds().width) / 2,
        rewardLabel.getPosition().y + rewardLabel.getGlobalBounds().height + 20
    );
}

void ScoreBoard::setScale(const sf::Vector2f& scale) {
    starShape.setScale(scale);
}
