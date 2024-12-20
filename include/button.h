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
    Button(sf::Vector2f position, const std::string& text);
    ~Button();

    bool isPressed() ;
    bool isHovered() ;
    void update(const sf::RenderWindow& window);
    void render(sf::RenderTarget& target);
};

#endif // BUTTON_H