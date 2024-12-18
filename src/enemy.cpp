#include "../include/enemy.h"
#include <SFML/Graphics.hpp>

Enemy::Enemy(int cell_size, sf::Vector2i start_position)
    : position(start_position) {
    // Initialize the enemy shape
    shape.setSize(sf::Vector2f(cell_size, cell_size));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(position.x * cell_size + 2.5f, position.y * cell_size + 2.5f); // Center in the cell
    shape.setScale(0.9f, 0.9f);
}

void Enemy::draw(sf::RenderWindow &window) {
    window.draw(shape);
}

sf::Vector2i Enemy::GetEnemyPosition() const {
    return position;
}

void Enemy::setPosition(sf::Vector2i new_position) {
    position = new_position;
    shape.setPosition(position.x * shape.getSize().x + 2.5f, position.y * shape.getSize().y + 2.5f);
}
