#ifndef HOUSE_H
#define HOUSE_H

#include "GameObject.h"

// The Parent Class (Basic House)
class House : public GameObject {
protected:
    float x, y; // Position variables
public:
    House(float startX, float startY);
};

// House 1: The Beige House with Red Roof
class House1 : public House {
public:
    House1(float startX, float startY);
    void draw() override;
};

// House 2: The Blue House with Siding and Chimney
class House2 : public House {
public:
    House2(float startX, float startY);
    void draw() override;
};

#endif
