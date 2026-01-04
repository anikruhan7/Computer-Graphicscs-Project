// Car.h
#ifndef CAR_H
#define CAR_H

#include "GameObject.h"

class Car : public GameObject
{
private:
    float x, y;
    float r, g, b;
    float direction; // +1 for right, -1 for left

public:
    Car(float startX, float startY, float red, float green, float blue, float dir);
    void draw() override;
    void update() override;
};

#endif