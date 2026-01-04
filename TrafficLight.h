#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "GameObject.h"

class TrafficLight : public GameObject
{
public:
    void draw() override;
    void update() override;
};

#endif