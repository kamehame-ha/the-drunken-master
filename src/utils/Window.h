//
// Created by mrlek on 25.04.2025.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <../../cmake-build-debug/_deps/sfml-src/include/SFML/Graphics.hpp>
#include <string>


class Window {
private:
    sf::VideoMode video_mode;
    std::string title;
    sf::Color default_color;

public:
    Window(sf::VideoMode video_mode, const std::string &title);

    auto create() const -> sf::RenderWindow;
};



#endif //WINDOW_H
