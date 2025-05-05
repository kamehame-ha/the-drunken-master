//
// Created by kame on 4/25/25.
//

#include "Hitbox.h"

#include "Player.h"

Hitbox::Hitbox(sf::RenderWindow &window): window(&window) {
    this->window = &window;
}