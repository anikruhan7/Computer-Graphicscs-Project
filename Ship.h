#ifndef SHIP_H
#define SHIP_H

#include "GameObject.h"

class Ship : public GameObject
{
private:
    float x, y, vx;
    float scale;

public:
    Ship(float px, float py, float speed, float s = 1.0f);
    void draw() override;
    void update() override;
};

#endif