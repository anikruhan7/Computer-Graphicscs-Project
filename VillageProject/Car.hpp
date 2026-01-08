#ifndef CAR_H
#define CAR_H
#include "GameObject.h"
class Car : public GameObject { private: float x, y, r, g, b, direction; public: Car(float startX, float startY, float red, float green, float blue, float dir); void draw() override; void update() override; };
#endif
