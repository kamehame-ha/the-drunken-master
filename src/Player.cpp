//
// Created by kame on 4/25/25.
//

#include "Player.h"

#include "fmt/printf.h"

Player::Player(int hp, int ad, const std::string &name) {
    this->hp = hp;
    this->ad = ad;
    this->name = name;

    this->moveSpeed = 300.f;  // Pixels per second
    this->velocityX = 0.f;
    this->velocityY = 0.f;
    this->gravity = 1000.f;
}

auto Player::create() -> void {
    const sf::CircleShape c(25.0f);
    this->shape = c;
    this->shape.setFillColor(sf::Color::White);
}

auto Player::getShape() -> sf::CircleShape {
    return this->shape;
}

auto Player::move(moveType type) -> void {
    switch (type) {
        case LEFT: walkLeft(); break;
        case DOWN: dropdown(); break;
        case RIGHT: walkRight(); break;
        case UP: jump(); break;
    }
}

auto Player::walkRight() -> void {
    velocityX += moveSpeed * 5;  // Add acceleration
    velocityX = std::min(velocityX, moveSpeed);  // Cap max speed
}

auto Player::walkLeft() -> void {
    velocityX -= moveSpeed * 5;  // Add acceleration
    velocityX = std::max(velocityX, -moveSpeed);  // Cap max speed
}

auto Player::jump() -> void {
    velocityY = -600.f;
}

auto Player::dropdown() -> void {

}

// Add the update method:
auto Player::update(float deltaTime) -> void {
    // Apply friction when no input
    if (velocityX > 0) {
        velocityX = std::max(0.0f, velocityX - moveSpeed * 2 * deltaTime);
    } else if (velocityX < 0) {
        velocityX = std::min(0.0f, velocityX + moveSpeed * 2 * deltaTime);
    }

    // Update position
    sf::Vector2f newPos = shape.getPosition();
    newPos.x += velocityX * deltaTime;
    newPos.y += velocityY * deltaTime;
    shape.setPosition(newPos);
}

