#ifndef PLANE_H
#define PLANE_H

#include "GameObject.h"

class Plane : public GameObject
{
private:
    float x, y, vx;
    float phase; // for bobbing

public:
    Plane(float px, float py, float speed);
    void draw() override;
    void update() override;
};

#endif