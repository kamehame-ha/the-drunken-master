//
// Created by mrlek on 25.04.2025.
//

#include "Window.h"

Window::Window(const sf::VideoMode video_mode, const std::string &title) {
    this->video_mode = video_mode;
    this->title = title;
}

auto Window::create() const -> sf::RenderWindow {
    return sf::RenderWindow(
        this->video_mode,
        this->title,
        sf::Style::Close,
        sf::State::Windowed,
        sf::ContextSettings({.antiAliasingLevel = 6})
    );
}


