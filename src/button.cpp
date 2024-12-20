#include "../include/button.h"

// Constructor
Button::Button(sf::Vector2f position, const std::string& text) {
    // Load textures for different status 
    if (!texIdle.loadFromFile("/Users/mobinzaki/Documents/GitHub/PLymouth-Uni-Maze-Game/assets/Buttons/" + text + "Button.png") ||
        !texHover.loadFromFile("/Users/mobinzaki/Documents/GitHub/PLymouth-Uni-Maze-Game/assets/Buttons/"+ text + "HOP.png") ||
        !texPressed.loadFromFile("/Users/mobinzaki/Documents/GitHub/PLymouth-Uni-Maze-Game/assets/Buttons/"+ text +"HOP.png")) {
        std::cerr << "Error loading button textures!" << std::endl;
    }
    //initialise the texture and position of the buttonn and etc
    buttonShape.setTexture(texIdle);
    buttonShape.setPosition(position);
    buttonShape.setScale(0.2, 0.2);

    //load the font and add error handeling
    try{
    if (font.loadFromFile("/Users/mobinzaki/Documents/GitHub/PLymouth-Uni-Maze-Game/assets/fonts/font.ttf"))
    {
        // std::cerr << "Font Loaded" << std::endl; for debugging
        return;  // Early exit on error
    }
    }catch (std::exception& e) {
        std::cerr << "Error loading font: " << e.what() << std::endl;// for debugging
        return; // Early exit on error//+
    }

    buttonText.setFont(font); // Set the font
    buttonText.setString(text);
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::Black); // Text color
    //center the button
    buttonText.setPosition(
        position.x + (buttonShape.getGlobalBounds().width - buttonText.getGlobalBounds().width) / 2,
        position.y + (buttonShape.getGlobalBounds().height - buttonText.getGlobalBounds().height) / 2
    );

    buttonState = IDLE; // Initial state
}

// Destructor
Button::~Button() {}

// Check if the button is pressed
bool Button::isPressed() {
    return buttonState == PRESSED;
}

// Check if the button is hovered
bool Button::isHovered() {
    return buttonState == HOVERED;
}

// Update the button state based on mouse position
void Button::update(const sf::RenderWindow& window) {
    buttonState = IDLE; // Reset state

    // Get mouse position
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        buttonState = HOVERED; // Mouse is over the button

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            buttonState = PRESSED; // Button is pressed
        }
    }

    // Change button texture based on state
    switch (buttonState) {
        case IDLE:
            buttonShape.setTexture(texIdle);
            break;
        case HOVERED:
            buttonShape.setTexture(texHover);
            break;
        case PRESSED:
            buttonShape.setTexture(texPressed);
            break;
    }
}

// Render the button
void Button::render(sf::RenderTarget& target) {
    target.draw(buttonShape);
    target.draw(buttonText);
}