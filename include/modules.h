#ifndef MODULES
#define MODULES

#include <string>
#include <iomanip>
#include <sstream>
#include "player.h"
#include "enemy.h"
#include "maze.h"
#include <chrono>
class Modules{
    public:
        std::string formatTime(int remainingTimeInSeconds);
        bool isPositionValid(const sf::Vector2i& position, const Player& player, const std::vector<Enemy>& enemies);
    private:
};


class Timer {
public:
    // Constructor
    Timer();

    // Start the timer with a duration in seconds
    void start(int durationInSeconds);

    // Check if the timer has expired
    bool check();
    
    // Reset the timer
    void reset(int newDurationInSeconds);

private:
    bool isTimerActive; // Flag to check if the timer is running
    int timerDuration;  // Duration in seconds
    std::chrono::steady_clock::time_point startTime; // Start time of the timer
};

#endif //MODULES