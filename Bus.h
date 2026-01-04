#ifndef BUS_H
#define BUS_H

#include "GameObject.h"

class Bus : public GameObject
{
private:
    float x, y;
    float direction; // +1 for right, -1 for left
    float speed;

public:
    Bus(float startX, float startY, float dir);
    void draw() override;
    void update() override;
};

#endif