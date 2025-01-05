#include "../include/game.h"
#include <filesystem>
Game::Game(sf::RenderWindow& window, std::string gameType)
    : window(window), gameType(gameType) // Initialize the window reference
{
    // std::cout << "Game Type is:" << gameType; // wheather the game is resumed or clicked on new game (for debugging)
}

// Function to check if a position is already occupied
bool Game::isPositionOccupied(const sf::Vector2i& pos, const std::vector<sf::Vector2i>& occupiedPositions) {
    return std::find(occupiedPositions.begin(), occupiedPositions.end(), pos) != occupiedPositions.end();
}


void Game::run(LevelManager& levelManager, double TimeLimitInSeconds){
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    // Load the game state if the game is resumed
    if (gameType == "Resumed") {
        //load the data from the file
        levelManager.loadGameState(playerPos, exitPos, enemyPositions, applesPositions, remainingTime, userScore, mazeStartPos);
        levelManager.setTimerLimit(remainingTime);
        std::cout << "Game state loaded successfully!" << std::endl;

    }

    // Retrieve the mazeWidth and mazeHeight values from the LevelManager class
    int mazeWidth = levelManager.getMazeWidth();
    int mazeHeight = levelManager.getMazeHeight();
    int enemySpeed = levelManager.getEnemySpeed();
    int enemyAmount = levelManager.getEnemyGenerateAmount();
    int userScore = levelManager.getUserScore();
    int currentLevel = levelManager.getCurrentLevel();

    if (gameType != "Resumed") {
        // Generate or load player position
        do {
            playerPos = sf::Vector2i(rand() % mazeWidth, rand() % mazeHeight);
        } while (isPositionOccupied(playerPos, occupiedPositions));
            occupiedPositions.push_back(playerPos); // Mark player position as occupied

       do {
            exitPos = sf::Vector2i(rand() % mazeWidth, rand() % mazeHeight);
        } while (isPositionOccupied(exitPos, occupiedPositions));
            occupiedPositions.push_back(exitPos); // Mark exit position as occupied

            sf::Vector2i mazeStartPos(rand() % mazeWidth, rand() % mazeHeight); // Default starting position
    }

    
    SettingsPopup settingsPopup(window);    // Create an instance of SettingsPopup
    Maze maze(mazeWidth, mazeHeight, 30, mazeStartPos.x, mazeStartPos.y);  // Create a Maze object
    Player player(30, playerPos); // Create Player object
    EscapeDoor escapeDoor(30, exitPos); //create Escape Door object
    WinOrLoose winOrLoose;
    Modules Module;
    Button HomeButton(sf::Vector2f(1110, 50), "Home");//create Home Page button

   
    // Get player and exit positions
    playerPos = player.GetPlayerPosition();
    sf::Vector2i goal = player.GetPlayerPosition();
    sf::Vector2i exit = escapeDoor.GetEscapeDoorPosition();
    
   // Create multiple enemies
for (int i = 0; i < enemyAmount; ++i) {
    sf::Vector2i randomPosition;

    if (gameType == "Resumed") {
        if (i < enemyPositions.size()) {
            // Use previously saved positions for resumed game
            randomPosition = enemyPositions[i];
        } else {
            // Handle case where there are more enemies than saved positions
            // For extra enemies, we need to generate new random positions
            do {
                randomPosition = sf::Vector2i(rand() % mazeWidth, rand() % mazeHeight);
            } while (isPositionOccupied(randomPosition, occupiedPositions));
            enemyPositions.push_back(randomPosition); // Save this position for potential future resumption
            occupiedPositions.push_back(randomPosition); // Mark position as occupied
        }
    } else {
        // Handle the creation of enemies for a new game
        do {
            randomPosition = sf::Vector2i(rand() % mazeWidth, rand() % mazeHeight);
        } while (isPositionOccupied(randomPosition, occupiedPositions));
        
        enemyPositions.push_back(randomPosition); // Save position for future resumption
        occupiedPositions.push_back(randomPosition); // Mark as occupied
    }

    // Create and add the enemy to the vector
    enemies.emplace_back(30, randomPosition); // Assuming 30 is the enemy size or health, adjust as needed
}


    
    // Vector to hold multiple Apples items
    // Generate 3 Apples items (all apples)
    for (int i = 0; i < 3; ++i) {
        sf::Vector2i randomApplesPosition;
        if (gameType == "Resumed" && i < applesPositions.size()) {
            randomApplesPosition = applesPositions[i]; // Use loaded positions for resumed game
        } else {
            do {
                randomApplesPosition = sf::Vector2i(rand() % mazeWidth, rand() % mazeHeight);
            } while (!Module.isPositionValid(randomApplesPosition, player, enemies)); // Ensure valid position
        }
        apples.emplace_back(30, randomApplesPosition); // Create an apple at the random position
    }
 
    // Path vector for A* algorithm
    std::vector<std::vector<sf::Vector2i>> paths(enemyAmount);
    bool pathNeedsUpdate = true; // Flag to control path recalculation

    // Movement cooldowns
    const int PlayerMoveCooldown = 50; // Player cooldown in milliseconds
    sf::Clock PlayerClock;

    //enemy speed
    const int EnemyMoveCooldown = enemySpeed; // Enemy cooldown in milliseconds
    std::vector<sf::Clock> enemyClocks(enemyAmount); // Separate clock for each enemy

    //timer for the game
    sf::Clock gameClock; // Clock to track the elapsed time

    sf::Clock PlayerAnimationCoolDown;
    // Enemy pause timer
     Timer timer;



    // Main game loop
    while (window.isOpen()) {
        //calculate the remaining time
        int elapsedTime = gameClock.getElapsedTime().asSeconds(); // Time since the game started
        remainingTime = levelManager.getTimerLimit() - elapsedTime;       // Time left

        
        //when time ends, player looses
        if (remainingTime <= 0) {
            std::cout << "Time's up! Player loses.\n";
            winOrLoose.showGameOverPopup(levelManager, window);
            return;
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                // Clear the vectors before updating
                enemyPositions.clear();
                applesPositions.clear();

                playerPos = player.GetPlayerPosition();
                // Update enemy positions
                for (size_t i = 0; i < enemies.size(); ++i) {
                    enemyPositions.push_back(enemies[i].GetEnemyPosition());
                }

                // Update apples positions
                for (size_t i = 0; i < apples.size(); ++i) {
                    applesPositions.push_back(apples[i].GetApplesPosition());
                }

                // Save the game state
                levelManager.saveGameState(playerPos, exitPos , enemyPositions, applesPositions,  remainingTime, levelManager.getUserScore(), mazeStartPos);
                window.close();
                return;
            }

            // Player movement with cooldown
            if (event.type == sf::Event::KeyPressed) {
                if (PlayerClock.getElapsedTime().asMilliseconds() >= PlayerMoveCooldown) {
                    if (event.key.code == sf::Keyboard::W) player.move(sf::Vector2i(0, -1), maze); // Move up
                    if (event.key.code == sf::Keyboard::S) player.move(sf::Vector2i(0, 1), maze);  // Move down
                    if (event.key.code == sf::Keyboard::A) player.move(sf::Vector2i(-1, 0), maze); // Move left
                    if (event.key.code == sf::Keyboard::D) player.move(sf::Vector2i(1, 0), maze);  // Move right


                    PlayerClock.restart();
                    pathNeedsUpdate = true; // Recalculate path when the player moves
                } 
            }
            
            if (event.type == sf::Event::MouseButtonPressed &&event.mouseButton.button == sf::Mouse::Left){
                if (HomeButton.isPressed(window)){
                    // Clear the vectors before updating
                    enemyPositions.clear();
                    applesPositions.clear();
                    playerPos = player.GetPlayerPosition();
                    // Update enemy positions
                    for (size_t i = 0; i < enemies.size(); ++i) {
                        enemyPositions.push_back(enemies[i].GetEnemyPosition());
                    }

                    // Update apples positions
                    for (size_t i = 0; i < apples.size(); ++i) {
                        applesPositions.push_back(apples[i].GetApplesPosition());
                    }
                    // std::cout<<"Home button pressed";
                    // Save the game state
                    levelManager.saveGameState(playerPos, exitPos , enemyPositions, applesPositions,  remainingTime, levelManager.getUserScore(), mazeStartPos);
                    levelManager.setTimerLimit(remainingTime);
                    Home mainMenu(window);  // Create a new instance of the main menu
                    mainMenu.run(levelManager); // Run the main menu
                    window.close(); //close the old one
                    return;
                }
            }
            
            HomeButton.update(window);
        }

        goal = player.GetPlayerPosition(); // Update player position
        exit = escapeDoor.GetEscapeDoorPosition();
        
        //check if any of the enemies found the player
        for (size_t i = 0; i < enemies.size(); ++i) {
            if (enemies[i].GetEnemyPosition() == goal) {
                std::cout << "Enemy " << i << " found the Player!" << std::endl;
                levelManager.setUserScore(-10);
                levelManager.setTimerLimit(120);
                levelManager.saveGameState(playerPos, exitPos , enemyPositions, applesPositions,  remainingTime, levelManager.getUserScore(), mazeStartPos);
                winOrLoose.showGameOverPopup(levelManager, window);
                return;
        }
        
        //check if Player ate one of the apples
        for(size_t i = 0; i < apples.size(); ++i){
            if (apples[i].GetApplesPosition() == goal){
                //stop the enemies
                for (size_t i = 0; i < enemies.size(); ++i){
                 if (enemies[i].GetEnemyPosition()!= goal) {
                    enemies[i].stop();
                    timer.start(8);
                    levelManager.setUserScore(5);
                    levelManager.setTimerLimit(remainingTime + 10);
                    std::cout << "Enemy " << i << " STOPED!" << std::endl;
                    
                 }
             }
                std::cout << "Player found an apple!" << std::endl;
                apples.erase(apples.begin() + i); // Remove the found apple from the list
                break;
            }
        }
    }      
        //Check if the player found the exit
          if (goal == exit) {
            std::cout << "Player found the exit!" << std::endl;
            // Immediately stop the game
            window.clear(sf::Color::Black);
            window.display();
            sf::sleep(sf::milliseconds(100)); // Short pause to allow rendering
            // Update maze
            maze.update();
            levelManager.setUserScore(10);
            std::cout << "user Score is: "<< levelManager.getUserScore();
            levelManager.calculateStars(remainingTime);
            levelManager.setTimerLimit(120);
            levelManager.saveGameState(playerPos, exitPos , enemyPositions, applesPositions,  remainingTime, levelManager.getUserScore(), mazeStartPos);
            winOrLoose.showLuckyDayPopup(levelManager, window); // Show the "Lucky Day" popup
            return; // Exit the game loop and end the game
        }

        // Update maze
        maze.update();

    //update path
       if (pathNeedsUpdate) {
        for (size_t i = 0; i < enemies.size(); ++i) {
            paths[i].clear();
            if (AStar::findPath(maze, enemies[i].GetEnemyPosition(), goal, paths[i], levelManager)) {
                std::cout << "Path for Enemy " << i << " found.\n";
            } else {
                std::cout << "No path for Enemy " << i << ".\n";
            }
        }
        pathNeedsUpdate = false;
    }


        // Move each enemy
        if (maze.getIsGenerated()){
            for (size_t i = 0; i < enemies.size(); ++i) {
                if (enemyClocks[i].getElapsedTime().asMilliseconds() >= EnemyMoveCooldown) {
                    if (!paths[i].empty()) {
                        sf::Vector2i nextStep = paths[i].front();
                        enemies[i].setPosition(nextStep);
                        paths[i].erase(paths[i].begin());
                    }
                    enemyClocks[i].restart();
                }
            }
        }

        // Check if the timer has expired
        if (timer.check()) {
            std::cout << "Timer expired! Action triggered.\n";
            // Resume the enemies
            for (size_t i = 0; i < enemies.size(); ++i) {
                enemies[i].resume();
            }
        }

        // Clear window and draw everything
        window.clear(sf::Color::Black);
        maze.draw(window);     // Draw maze

        if (maze.getIsGenerated()) {
            sf::Time deltaTime = PlayerAnimationCoolDown.restart();
            if (maze.allCellsVisited() && !maze.isWallsRemoved()){
                // Create additional exits and remove some walls randomly
                int additionalExits = 8; // Number of additional exits to create
                maze.removeRandomWalls(additionalExits); // Set the flag to true when generation is complete
                std::cout<<"walls removed"<< additionalExits;
            }

            escapeDoor.draw(window); // Draw escape door
            player.draw(window); // Draw player
            player.update(deltaTime.asSeconds());

            // Draw each enemy
            for (auto& enemy : enemies) 
            {
                enemy.draw(window); 
            }
            // draw all the Apples items
            for (auto& Apples : apples)
            {
                Apples.draw(window); // Draw each Apples item
            }
        }

        HomeButton.render(window);
        // Display the time remaining
            sf::Text timerText;
            sf::Font font;
            // Get the current working directory
            std::string currentDir = std::filesystem::current_path().string();
            // Load the font from the assets folder
            if (font.loadFromFile(currentDir + "/assets/fonts/font.ttf")) { // Replace with your font path
                timerText.setFont(font);
                timerText.setCharacterSize(20);
                //display the timer in the right format 00:00
                timerText.setString(Module.formatTime(remainingTime));
                timerText.setFillColor(sf::Color::Red);
                timerText.setPosition(1100, 10); // Adjust position as needed
                window.draw(timerText);

            }
        window.display();
    }

}
