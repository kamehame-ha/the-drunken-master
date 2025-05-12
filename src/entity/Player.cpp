//
// Created by kame on 4/25/25.
//

#include "Player.h"
#include "../map_utils/Hitbox.h"
#include "fmt/printf.h"

Player::Player(GameSave::PlayerData &data): player_data(data) {
    player_data = data;
    velocityX = 0.f;
    velocityY = 0.f;
    gravity = 1000.f;

    onGround = false;
}

auto Player::create() -> void {
    const sf::CircleShape c(30.0f);
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

auto Player::setOnElement(bool value) -> void {
    onElement = value;
}

auto Player::getOnElement() const -> bool {
    return onElement;
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

auto Player::trapDamage() -> void {
    velocityY = -300.0f;
    onGround = false;
    canJump = false;
}

auto Player::stopX() -> void {
    velocityX = 0.f;
}

auto Player::stopY() -> void {
    velocityY = 0.f;
}


// Add the update method:

auto Player::update(float deltaTime) -> void {
    // Handle horizontal movement
    updateHorizontalMovement(deltaTime);

    // Apply gravity if not on ground or element
    if (!onGround || !onElement) {
        velocityY += gravity * deltaTime;
    }

    // Update position
    shape.move(sf::Vector2f(velocityX * deltaTime, velocityY * deltaTime));
}

auto Player::updateHorizontalMovement(float deltaTime) -> void {
    const float acceleration = onGround  ? player_data.move_speed * 10 : player_data.move_speed * 5;

    if (movingRight) {
        velocityX = std::min(velocityX + acceleration * deltaTime, player_data.move_speed);
    }
    else if (movingLeft) {
        velocityX = std::max(velocityX - acceleration * deltaTime, -player_data.move_speed);
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

auto Player::getPlayerData() -> GameSave::PlayerData& {
    return player_data;
}

auto Player::setPlayerData(GameSave::PlayerData& data) -> void {
    player_data = data;
}
