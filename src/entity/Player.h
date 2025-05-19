//
// Created by kame on 4/25/25.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <string>
#include "../save_utils/GameSave.h"

class Player {
private:
    GameSave::PlayerData player_data;
    sf::CircleShape shape;

    float gravity;
    bool onGround;

    bool canJump = true;

    // hitbox needed value
    bool onElement = false;

    auto walkLeft() -> void;
    auto walkRight() -> void;
    auto jump() -> void;

    bool movingLeft = false;
    bool movingRight = false;

public:
    Player(const GameSave::PlayerData &data);

    auto create() -> void;
    auto getShape() -> sf::CircleShape&;

    // Moving
    enum moveType {
        UP, LEFT, RIGHT
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

    auto getPlayerData() -> GameSave::PlayerData&;
    auto setPlayerData(const GameSave::PlayerData& data) -> void;
};



#endif //PLAYER_H
