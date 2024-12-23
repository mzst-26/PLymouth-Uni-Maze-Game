#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/home.h"

Home::Home(sf::RenderWindow& window)
    :window(window),
      playButton(sf::Vector2f(550, 200), "NewPlay"),
      resumeButton(sf::Vector2f(550, 260), "Resume"),
      settingsButton(sf::Vector2f(550, 320), "Settings"),
      quitButton(sf::Vector2f(550, 380), "Quit"),
      fadeRect(sf::Vector2f(1200, 800)),
      settingsPopup(window),
      loading(false),
      showSettings(false) {
    // Load background texture
    if (!backgroundTexture.loadFromFile("/Users/mobinzaki/Documents/GitHub/PLymouth-Uni-Maze-Game/assets/Backgrounds/MazeImageBackground.png")) {
        std::cerr << "Error loading background image!" << std::endl;
        exit(-1);
    }
    background.setTexture(backgroundTexture);
    background.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    // Initialize fade rectangle
    fadeRect.setFillColor(sf::Color(0, 0, 0, 0)); // Transparent at the start
}

Home::~Home() {
    // Destructor, cleanup if necessary
}

void Home::run(LevelManager& levelManager) {
    while (window.isOpen()) {
        handleEvents(levelManager);
        update(levelManager);
        render();
    }
}

void Home::handleEvents(LevelManager& levelManager) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (playButton.isPressed(window)) {
                loading = true;
                loadingClock.restart();
            }
            if (resumeButton.isPressed(window)) {
                std::cout << "Resume clicked\n";
                // TODO: Implement resume logic
            }
            if (settingsButton.isPressed(window)) {
                showSettings = !showSettings;
            }
            if (quitButton.isPressed(window)) {
                window.close();
            }
        }

        if (showSettings) {
            settingsPopup.handleInput(event, levelManager);
        }
    }
}

void Home::update(LevelManager& levelManager) {
    playButton.update(window);
    resumeButton.update(window);
    settingsButton.update(window);
    quitButton.update(window);

    if (loading) {
        sf::Color fadeColor = fadeRect.getFillColor();
        if (fadeColor.a < 255) {
            fadeColor.a += 5; // Fade effect
            fadeRect.setFillColor(fadeColor);
        } else if (loadingClock.getElapsedTime().asSeconds() >= 2.0f) {
            Game game(window);
            game.run(levelManager); // Run the game
            return;                 // Exit the home menu
        }
    }
}

void Home::render() {
    window.clear();
    window.draw(background);
    playButton.render(window);
    resumeButton.render(window);
    settingsButton.render(window);
    quitButton.render(window);

    if (showSettings) {
        settingsPopup.render();
    }

    if (loading) {
        window.draw(fadeRect);
    }

    window.display();
}