#ifndef BIRD_H
#define BIRD_H

#include "GameObject.h"

class Bird : public GameObject
{
private:
    float x, y;
    float speed;

public:
    Bird(float startX, float startY, float s);
    void draw() override;
    void update() override;
};

#endif