//
// Created by kame on 5/6/25.
//

#ifndef GROUND_H
#define GROUND_H
#include "Element.h"



class Ground : public Element {
private:
    sf::RectangleShape shape;

public:
    Ground();

    void create() {
        const sf::RectangleShape r(sf::Vector2f(2000.0f, 50.0f));
        this->shape.setFillColor(sf::Color(0x8c512c));

    }

    sf::RectangleShape& getShape() {
        return shape;
    }
};



#endif //GROUND_H
