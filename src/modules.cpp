#include "../include/modules.h"
#include <iostream>
// Function to format remaining time as "MM:SS"
std::string Modules::formatTime(int remainingTimeInSeconds) {
    int minutes = remainingTimeInSeconds / 60;
    int seconds = remainingTimeInSeconds % 60;

    std::ostringstream formattedTime;
    formattedTime << std::setfill('0') << std::setw(2) << minutes << ":"
                  << std::setfill('0') << std::setw(2) << seconds;

    return formattedTime.str();
}
bool Modules::isPositionValid(const sf::Vector2i& position, const Player& player, const std::vector<Enemy>& enemies) {
    if (position == player.GetPlayerPosition()) return false; // Overlaps with player
    for (const auto& enemy : enemies) {
        if (position == enemy.GetEnemyPosition()) return false; // Overlaps with any enemy
    }
    return true;
}
