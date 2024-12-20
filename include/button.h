#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

//Status of the button for easy handeling
  enum ButtonState {
            IDLE = 0,
            HOVERED = 1,
            PRESSED = 2
    };
class Button {
private:
    //initialise 
    std::vector<std::string> buttonVariants{"NewPlay", "Resume", "Quit", "Settings"};
    sf::Sprite buttonShape;
    sf::Color colorIdle;
    sf::Color colorHover;
    sf::Color colorPressed;
    sf::Text buttonText;
    sf::Texture texIdle;
    sf::Texture texHover;
    sf::Texture texPressed;
    int buttonState;
    sf::Font font;

public:
    // Public method to get the current button state
    ButtonState getButtonState() const {
        return static_cast<ButtonState>(buttonState); // Return the current state as ButtonState
    }
      // Public method to set the button state
    void setButtonState(ButtonState state) {
        buttonState = state; // Set the button state
        // Optionally, you can also update the button texture here if needed
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
    void setScale(const sf::Vector2f& scale);

    Button(sf::Vector2f position, const std::string& text);
    ~Button();

    bool isPressed(const sf::RenderWindow& window) const;
    bool isHovered() ;
    bool isRest();
    void update(const sf::RenderWindow& window);
    void render(sf::RenderTarget& target);
    // bool Button::setHighlighted(bool highlighted, std::string text);
};

#endif // BUTTON_H