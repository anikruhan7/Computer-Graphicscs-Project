#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "GameObject.h"

// Variables shared with Scene.cpp
extern bool isDay;
extern float cloudX;
extern float sunY;

class Background : public GameObject
{
public:
    void draw() override;
    void update() override;
};

#endif