#include "../include/button.h"
#include <filesystem>
// Constructor
Button::Button(sf::Vector2f position, const std::string& text) {
    // Load textures for different status
    // Get the current working directory
        std::string currentDir = std::filesystem::current_path().string();
       std::string basePath = currentDir + "/assets/Buttons/";
    if (!texIdle.loadFromFile(basePath + text + "Button.png") ||
        !texHover.loadFromFile(basePath + text + "HOP.png") ||
        !texPressed.loadFromFile(basePath + text + "HOP.png")) {
        std::cerr << "Error loading button textures!" << std::endl;
    }
    // Initialize the texture and position of the button
    buttonShape.setTexture(texIdle);
    buttonShape.setPosition(position);
    if (text == "Easy" || text == "Medium" || text == "Hard"){
          buttonShape.setScale(1, 1);
    }else{
        buttonShape.setScale(0.2f, 0.2f);
    }
    //load the font and add error handeling
    try{
    if (font.loadFromFile(currentDir + "/assets/fonts/font.ttf"))
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
bool Button::isPressed(const sf::RenderWindow& window) const {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window); // Get mouse position relative to the window
    sf::FloatRect buttonBounds = buttonShape.getGlobalBounds(); // Get the button's bounding box
    buttonState == PRESSED; 
    return buttonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)); // Check if the mouse is inside the button
}

// Check if the button is hovered
bool Button::isHovered() {
    return buttonState == HOVERED;

}

// Check if the button is hovered
bool Button::isRest() {
    return buttonState == IDLE;
}

// Update the button state based on mouse position
// In Button::update()
void Button::update(const sf::RenderWindow& window) {
    buttonState = IDLE; // Reset state

    // Get mouse position
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        buttonState = HOVERED; // Mouse is over the button

        // Check if the mouse button is pressed
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

void Button::setScale(const sf::Vector2f& scale) {
    buttonShape.setScale(scale); // Set the scale of the button's sprite
}