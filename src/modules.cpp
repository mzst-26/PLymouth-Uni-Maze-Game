#include "../include/modules.h"
#include <iostream>
#include <chrono>

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

Timer::Timer() : isTimerActive(false), timerDuration(0) {}

// Start the timer with a duration in seconds
void Timer::start(int durationInSeconds) {
    startTime = std::chrono::steady_clock::now(); // Record the current time
    timerDuration = durationInSeconds; // Set the duration
    isTimerActive = true;
}

// Check if the timer has expired
bool Timer::check() {
    if (isTimerActive) {
        auto now = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
        
        if (elapsedTime >= timerDuration) {
            isTimerActive = false; // Timer has finished
            return true; // Time has expired
        }
    }
    return false; // Timer is still running
}


// Reset the timer with a new duration
void Timer::reset(int newDurationInSeconds) {
    startTime = std::chrono::steady_clock::now(); // Record the current time again
    timerDuration = newDurationInSeconds; // Set the new duration
    isTimerActive = true; // Ensure the timer is active
}
