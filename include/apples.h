#ifndef Apples_H
#define Apples_H

#include <SFML/Graphics.hpp>

class Apples {
public:
    Apples(float size, sf::Vector2i position); // Constructor
    void draw(sf::RenderWindow& window);     // Draw Apples sprite
    sf::Vector2i GetApplesPosition() const;    // Get Apples position

private:
    sf::Vector2i position;          // Position of the Apples
    sf::Sprite sprite;              // Sprite for rendering Apples
    static sf::Texture texture;     // Shared texture for all Apples items
};

#endif // Apples_H