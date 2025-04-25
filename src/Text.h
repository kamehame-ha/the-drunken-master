//
// Created by kame on 4/25/25.
//

#ifndef TEXT_H
#define TEXT_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "Wrapper.h"

class Text {
private:
    sf::RenderWindow* window;
    sf::Font font;
    std::string font_path;
    int text_size; // 24
    int gap; // 10
    Wrapper wrapper;

    auto center_even(const std::vector<sf::Text> &vector) -> void;
    auto center_not_even(const std::vector<sf::Text> &vector) -> void;

public:
    explicit Text(sf::RenderWindow &window);

    auto renderText(const sf::Text &text) const -> void;
    auto renderText(const std::vector<sf::Text> &vector) const -> void;
    auto createText() -> sf::Text;

    auto centerTextLines(std::vector<sf::Text> &vector) -> std::vector<sf::Text>;

    // Setters
    auto setFont(const sf::Font &font) -> void;
    auto setFontPath(const std::string &font_path) -> void;
    auto setTextSize(int size) -> void;
    auto setGap(int size) -> void;

    // Getters
    auto getFont() -> sf::Font;
    auto getFontPath() -> std::string;
    auto getTextSize() const -> int;
    auto getGap() const -> int;
};



#endif //TEXT_H
