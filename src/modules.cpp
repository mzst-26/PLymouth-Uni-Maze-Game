#include "../include/modules.h"

// Function to format remaining time as "MM:SS"
std::string Modules::formatTime(int remainingTimeInSeconds) {
    int minutes = remainingTimeInSeconds / 60;
    int seconds = remainingTimeInSeconds % 60;

    std::ostringstream formattedTime;
    formattedTime << std::setfill('0') << std::setw(2) << minutes << ":"
                  << std::setfill('0') << std::setw(2) << seconds;

    return formattedTime.str();
}