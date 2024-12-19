#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>


class Button {
private:
    sf::Sprite buttonShape;
    sf:: Color colorIdle;
    sf::Color colorHover;
    sf::Text buttonText;
    sf::Texture texIdle;
    sf::Texture texHover;
    sf::Texture texPressed;
    int buttonState;
    sf::Font font;



public:
    Button(sf::Vector2f mousPositionView);
    ~Button();

    const bool& isPressed() const;
    const bool& isHovered() const;
    void update(const sf::RenderWindow& window);
    void render(sf::RenderTarget& target);
};