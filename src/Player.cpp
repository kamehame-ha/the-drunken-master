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

    moveSpeed = 300.f; // Pixels per second
    velocityX = 0.f;
    velocityY = 0.f;
    gravity = 1000.f;

    onGround = false;
}

auto Player::create() -> void {
    const sf::CircleShape c(25.0f);
    shape = c;
    shape.setFillColor(sf::Color::White);
}

auto Player::isOnGround() -> bool {
    return onGround;
}

auto Player::setOnGround(bool value) -> void {
    onGround = value;
}

auto Player::setCanJump(bool value) -> void {
    canJump = value;
}

auto Player::getCanJump() -> bool {
    return canJump;
}

auto Player::getShape() -> sf::CircleShape& {
    return shape;
}

auto Player::setPosition(float x, float y) -> void {
    shape.setPosition(sf::Vector2f(x, y));
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
    movingRight = true;
    movingLeft = false;
}

auto Player::walkLeft() -> void {
    movingLeft = true;
    movingRight = false;
}

auto Player::jump() -> void {
    if (canJump) {
        velocityY = -600.f;
        onGround = false;
        canJump = false;  // Disable jumping until next ground touch
    }
}

auto Player::dropdown() -> void {

}

auto Player::stopX() -> void {
    velocityX = 0.f;
    movement.x = 0.f;
}

auto Player::stopY() -> void {
    velocityY = 0.f;
    movement.y = 0.f;
}


// Add the update method:

auto Player::update(float deltaTime) -> void {
    // Handle horizontal movement
    updateHorizontalMovement(deltaTime);

    // Apply gravity if not on ground
    if (!onGround) {
        velocityY += gravity * deltaTime;
    }

    // Update position
    shape.move(sf::Vector2f(velocityX * deltaTime, velocityY * deltaTime));
    movement = sf::Vector2f(velocityX * deltaTime, velocityY * deltaTime);
}

auto Player::updateHorizontalMovement(float deltaTime) -> void {
    const float acceleration = onGround ? moveSpeed * 10 : moveSpeed * 5;

    if (movingRight) {
        velocityX = std::min(velocityX + acceleration * deltaTime, moveSpeed);
    }
    else if (movingLeft) {
        velocityX = std::max(velocityX - acceleration * deltaTime, -moveSpeed);
    }
    else if (onGround) {
        velocityX = 0; // Only stop instantly on ground
    }
}

auto Player::handleInputRelease(sf::Keyboard::Key key) -> void {
    if (key == sf::Keyboard::Key::A) {
        movingLeft = false;
    }
    else if (key == sf::Keyboard::Key::D) {
        movingRight = false;
    }
}