//
// Created by kame on 4/25/25.
//

#include "Text.h"
#include <vector>
#include "Wrapper.h"
#include <string>
#include <SFML/Graphics.hpp>

Text::Text() {
    text_size = 24;
    gap = 10;
    font = sf::Font();
}

// auto Text::center_even(std::vector<sf::Text> &vector) -> void {
//     auto [top, bottom] = std::make_pair((vector.size() / 2) - 1, vector.size() / 2);
//
//     for (int i = 0; i < vector.size(); i++) {
//         sf::Text &line = vector[i];
//
//         auto [x, y] = wrapper.center(line);
//
//         auto y_top = y - (gap / 2) - (text_size / 2);
//         auto y_bottom = y + (gap / 2) + (text_size / 2);
//
//         if (i == top) {
//             line.setPosition(sf::Vector2f(x, y_top));
//         } else if (i == bottom) {
//             line.setPosition(sf::Vector2f(x, y_bottom));
//         } else if (i < top) {
//             line.setPosition(sf::Vector2f(x, y_top - (text_size * (top - i)) - (gap * (top - i))));
//         } else if (i > bottom) {
//             line.setPosition(sf::Vector2f(x, y_bottom + (text_size * (i - bottom)) + (gap * (i - bottom))));
//         }
//     }
// }
//
// auto Text::center_not_even(std::vector<sf::Text> &vector) -> void {
//     const int center_line_index = int(vector.size() / 2);
//
//     for (int i = 0; i < vector.size(); i++) {
//         sf::Text &line = vector[i];
//
//         auto [x, y] = wrapper.center(line);
//
//         auto y_plus = (y + (text_size * (i - center_line_index))) + (gap * (i - center_line_index));
//         auto y_minus = (y - (text_size * (center_line_index - i))) - (gap * (center_line_index - i));
//
//         if (i == center_line_index) {
//             line.setPosition(sf::Vector2f(x, y));
//         } else if (i > center_line_index) {
//             line.setPosition(sf::Vector2f(x, y_plus));
//         } else if (i < center_line_index) {
//             line.setPosition(sf::Vector2f(x, y_minus));
//         }
//     }
// }

auto Text::renderText(const sf::Text &text, sf::RenderWindow &window) const -> void {
    window.draw(text);
}

auto Text::renderText(const std::vector<sf::Text> &vector, sf::RenderWindow &window) const -> void {
    for (const auto text : vector) {
        window.draw(text);
    }
}


auto Text::createText() -> sf::Text {
    if (!font.openFromFile(font_path)) {
        throw std::runtime_error("Failed to load font");
    }

    return sf::Text(font);
}

// auto Text::centerTextLines(std::vector<sf::Text> &vector) -> std::vector<sf::Text> {
//     if (vector.size() % 2 != 0) {
//         center_not_even(vector);
//     } else {
//         center_even(vector);
//     }
//
//     return vector;
// }

auto Text::setFont(const sf::Font &font) -> void {
    this->font = font;
}

auto Text::setFontPath(const std::string &font_path) -> void {
    this->font_path = font_path;
}

auto Text::setTextSize(const int size) -> void {
    text_size = size;
}

auto Text::setGap(const int size) -> void {
    gap = size;
}

auto Text::getFont() -> sf::Font {
    return font;
}

auto Text::getFontPath() -> std::string {
    return font_path;
}

auto Text::getTextSize() const -> int {
    return text_size;
}

auto Text::getGap() const -> int {
    return gap;
}