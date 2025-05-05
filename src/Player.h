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

    float velocityX;
    float velocityY;
    float gravity;

    auto walkLeft() -> void;
    auto walkRight() -> void;
    auto jump() -> void;
    auto dropdown() -> void;

public:
    Player(int hp, int ad, const std::string &name);

    auto create() -> void;
    auto getShape() -> sf::CircleShape;

    // Moving
    enum moveType {
        UP, DOWN, LEFT, RIGHT
    };

    auto move(moveType type) -> void;

    auto update(float deltaTime) -> void;
};



#endif //PLAYER_H
