#include "../include/game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>  // For rand()
#include "../include/a_star.h"
#include "../include/settingsPopup.h"
#include "../include/escape.h"
#include "../include/levelManager.h"
#include "../include/winOrLoosePopup.h"
#include "../include/home.h"
#include "../include/modules.h"
#include "../include/apples.h"
Game::Game(sf::RenderWindow& window)
    : window(window) // Initialize the window reference
{
    // Additional initialization if necessary
}

void Game::run(LevelManager& levelManager, int timeLimitMinutes){
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    // Create a render window
    // sf::RenderWindow window(sf::VideoMode(1200, 800), "Mystery Maze");

    // Create an instance of SettingsPopup
    SettingsPopup settingsPopup(window);

    //initialise the Maze width and height
    int mazeWidth = levelManager.getMazeWidth();
    int mazeHeight = levelManager.getMazeHeight();
    int enemySpeed = levelManager.getEnemySpeed();
    int enemyAmount = levelManager.getEnemyGenerateAmount();
    
    std::vector<Enemy> enemies; // Vector to hold multiple enemies
    // Create a Maze object
    Maze maze(mazeWidth, mazeHeight, 30, 0, 0);
    // Create Player and Enemy objects
    Player player(30, sf::Vector2i(rand() % mazeWidth, rand() % mazeHeight));

    //create Escape Door object
    EscapeDoor escapeDoor(30, sf::Vector2i(rand() % mazeWidth, rand() % mazeHeight));
    //win or loose
    WinOrLoose winOrLoose;
    //Modules
    Modules Module;
    // Create multiple enemies
    for (int i = 0; i < enemyAmount; ++i) {
        sf::Vector2i randomPosition(rand() % mazeWidth, rand() % mazeHeight);
        enemies.emplace_back(30, randomPosition); // Create and add an enemy to the vector
    }

    // Apples Apples(30,sf::Vector2i(rand() % mazeWidth, rand() % mazeHeight), "apple" );
    std::vector<Apples> apples; // Vector to hold multiple Apples items
    // Generate 3 Apples items (all apples)
    for (int i = 0; i < 3; ++i) {
        sf::Vector2i randomApplesPosition;
        do {
            randomApplesPosition = sf::Vector2i(rand() % mazeWidth, rand() % mazeHeight);
        } while (!Module.isPositionValid(randomApplesPosition, player, enemies));
        apples.emplace_back(30, randomApplesPosition); // Create an apple at the random position
    }

    //create Home Page button
    Button HomeButton(sf::Vector2f(1110, 50), "Home");

    // Get player and exit positions
    sf::Vector2i goal = player.GetPlayerPosition();
    sf::Vector2i exit = escapeDoor.GetEscapeDoorPosition();
  
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
    int timeLimitSeconds = timeLimitMinutes * 60; // convert min to sec


    // Main game loop
    while (window.isOpen()) {
        //calculate the remaining time
        int elapsedTime = gameClock.getElapsedTime().asSeconds(); // Time since the game started
        int remainingTime = timeLimitSeconds - elapsedTime;       // Time left
        //when time ends, player looses
        if (remainingTime <= 0) {
            std::cout << "Time's up! Player loses.\n";
            winOrLoose.showGameOverPopup(levelManager, window);
            return;
        }


        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
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
                    Home mainMenu(window);  // Create a new instance of the main menu
                    mainMenu.run(levelManager); // Run the main menu
                    window.close();
                    return;
                }
            }
            HomeButton.update(window);
            
        }

        goal = player.GetPlayerPosition(); // Update player position
        exit = escapeDoor.GetEscapeDoorPosition();
        
         for (size_t i = 0; i < enemies.size(); ++i) {
        if (enemies[i].GetEnemyPosition() == goal) {
            std::cout << "Enemy " << i << " found the Player!" << std::endl;
            winOrLoose.showGameOverPopup(levelManager, window);
            return;
        }
        for(size_t i = 0; i < apples.size(); ++i){
            if (apples[i].GetApplesPosition() == goal){
                std::cout << "Player found an apple!" << std::endl;
                apples.erase(apples.begin() + i); // Remove the found apple from the list
                break;
            }
        }
    }
          if (goal == exit) {
            std::cout << "Player found the exit!" << std::endl;
            // Immediately stop the game
            window.clear(sf::Color::Black);
            window.display();
            sf::sleep(sf::milliseconds(100)); // Short pause to allow rendering
            // Update maze
            maze.update();
            winOrLoose.showLuckyDayPopup(levelManager, window); // Show the "Lucky Day" popup
            return; // Exit the game loop and end the game
        }

        // Update maze
        maze.update();

        // Recalculate the path if needed
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

        // Clear window and draw everything
        window.clear(sf::Color::Black);
        
        maze.draw(window);     // Draw maze
        if (maze.getIsGenerated()) {
            if (maze.allCellsVisited() && !maze.isWallsRemoved()){
            // Create additional exits and remove some walls randomly
            int additionalExits = 8; // Number of additional exits to create
            maze.removeRandomWalls(additionalExits); // Set the flag to true when generation is complete
            std::cout<<"walls removed"<< additionalExits;
             }
            escapeDoor.draw(window); // Draw escape door
            player.draw(window); // Draw player
            for (auto& enemy : enemies) {
                enemy.draw(window); // Draw each enemy
            }
           
         
            
            // draw all the Apples items
            for (auto& Apples : apples) {
                Apples.draw(window); // Draw each Apples item
            }
        }
        HomeButton.render(window);
        // Display the time remaining
            sf::Text timerText;
            sf::Font font;
            if (font.loadFromFile("/Users/mobinzaki/Documents/GitHub/PLymouth-Uni-Maze-Game/assets/fonts/font.ttf")) { // Replace with your font path
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
