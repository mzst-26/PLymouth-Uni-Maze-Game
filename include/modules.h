#ifndef MODULES
#define MODULES

#include <string>
#include <iomanip>
#include <sstream>
#include "player.h"
#include "enemy.h"
#include "maze.h"

class Modules{
    public:
        std::string formatTime(int remainingTimeInSeconds);
        bool isPositionValid(const sf::Vector2i& position, const Player& player, const std::vector<Enemy>& enemies);
    private:
};

#endif //MODULES