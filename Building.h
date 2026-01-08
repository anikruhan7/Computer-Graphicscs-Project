#ifndef BUILDING_H
#define BUILDING_H

#include "GameObject.h"

class Building : public GameObject
{
private:
    float x, y, w, h;
    float r, g, b;

public:
    Building(float px, float py, float pw, float ph, float red, float green, float blue);
    void draw() override;
};

#endif