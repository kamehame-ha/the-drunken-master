//
// Created by kame on 4/25/25.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <string>

class Player {
private:
    int hp = 0;
    int ad = 0;
    std::string name;
    int level = 0;
    sf::CircleShape shape;
    float moveSpeed;

    float gravity;
    bool onGround;

    bool canJump = true;

    // hitbox needed value
    bool onElement = false;

    auto walkLeft() -> void;
    auto walkRight() -> void;
    auto jump() -> void;
    auto dropdown() -> void;

    bool movingLeft = false;
    bool movingRight = false;

public:
    Player(int hp, int ad, const std::string &name);

    auto create() -> void;
    auto getShape() -> sf::CircleShape&;

    // Moving
    enum moveType {
        UP, DOWN, LEFT, RIGHT
    };

    sf::Vector2f movement;
    float velocityX;
    float velocityY;

    auto move(moveType type) -> void;

    auto update(float deltaTime) -> void;
    auto updateHorizontalMovement(float deltaTime) -> void;
    auto handleInputRelease(sf::Keyboard::Key key) -> void;

    auto stopX() -> void;
    auto stopY() -> void;

    auto setPosition(float x, float y) -> void;

    auto isOnGround() -> bool;
    auto setOnGround(bool value) -> void;

    auto setCanJump(bool value) -> void;
    auto getCanJump() -> bool;

    auto setOnElement(bool value) -> void;
    auto getOnElement() const -> bool;
};



#endif //PLAYER_H
