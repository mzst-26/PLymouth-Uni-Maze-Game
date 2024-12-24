#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <SFML/Graphics.hpp>
#include <string>

class ScoreBoard {
public:
    // Constructor
    ScoreBoard(sf::Vector2f position, const std::string& fileName, const std::string& text);

    // Destructor
    ~ScoreBoard();

    // Render the star and text
    void render(sf::RenderTarget& target);

    // Update the reward amount text
    void updateRewardAmount(const std::string& amount);

    // Set the scale of the star shape
    void setScale(const sf::Vector2f& scale);

private:
    // Text objects
    sf::Text rewardLabel;   // For "Your Reward"
    sf::Text rewardAmount;  // For the dynamic amount

    // Star shape
    sf::Sprite starShape;
    sf::Texture texIdle;
    sf::Texture texActive;

    // Font object
    sf::Font font;

    // Star state (for future use, e.g., active or idle)
    enum StarState { IDLE, ACTIVE } starState;
};

#endif // SCOREBOARD_H
