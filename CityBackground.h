#ifndef CITYBACKGROUND_H
#define CITYBACKGROUND_H

#include "GameObject.h"

// Globals used by other objects to sync water animation
extern float cityWaterPhase;
extern float cityWaterSurfaceY;

class CityBackground : public GameObject
{
public:
    void draw() override;
    void update() override;
};

#endif