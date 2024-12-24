#ifndef STAR_H
#define STAR_H

#include <SFML/Graphics.hpp>
#include <string>

class Star {
public:
    // Enum for star states
    enum State {
        IDLE,
        ACTIVE
    };

    // Constructor and Destructor
    Star(sf::Vector2f position, const std::string& text);
    ~Star();

    // Methods
    void setActive(bool active);           // Toggle star state
    bool isActive() const;                 // Check if the star is active
    void render(sf::RenderTarget& target); // Render the star
    void setScale(const sf::Vector2f& scale); // Set the star's scale

private:
    // Textures for the star
    sf::Texture texIdle;
    sf::Texture texActive;

    // Visual representation of the star
    sf::Sprite starShape;

    // Text for labeling the star
    sf::Text starText;

    // Font for the text
    sf::Font font;

    // Current state of the star
    State starState;
};

#endif // STAR_H
