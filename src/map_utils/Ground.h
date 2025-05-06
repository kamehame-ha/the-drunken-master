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

    }

    sf::RectangleShape& getShape() {

    }
};



#endif //GROUND_H
