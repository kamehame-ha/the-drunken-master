//
// Created by kame on 4/25/25.
//

#include "Player.h"

#include "Hitbox.h"
#include "fmt/printf.h"

Player::Player(int hp, int ad, const std::string &name) {
    this->hp = hp;
    this->ad = ad;
    this->name = name;

    moveSpeed = 300.f;  // Pixels per second
    velocityX = 0.f;
    velocityY = 0.f;
    gravity = 1000.f;
}

auto Player::create() -> void {
    const sf::CircleShape c(25.0f);
    shape = c;
    shape.setFillColor(sf::Color::White);
}

auto Player::getShape() -> sf::CircleShape {
    return shape;
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
    Hitbox::onGround = false;
}

auto Player::dropdown() -> void {

}

auto Player::stopX() -> void {
    velocityX = 0.f;
}

auto Player::stopY() -> void {
    velocityY = 0.f;
}


// Add the update method:
auto Player::update(float deltaTime) -> void {
    if (!Hitbox::onGround) {
        velocityY += gravity * deltaTime;
    }

    // Apply friction when no input
    if (velocityX > 0) {
        velocityX = std::max(0.0f, velocityX - moveSpeed * 2 * deltaTime);
    } else if (velocityX < 0) {
        velocityX = std::min(0.0f, velocityX + moveSpeed * 2 * deltaTime);
    }

    movement = sf::Vector2f(velocityX * deltaTime, velocityY * deltaTime);

    // Update position
    sf::Vector2f newPos = shape.getPosition();
    newPos.x += velocityX * deltaTime;
    newPos.y += velocityY * deltaTime;
    shape.setPosition(newPos);
}

