#ifndef RAIN_H
#define RAIN_H
#include "GameObject.h"
#include <vector>
struct RainDrop { float x, y, speed, length; };
class Rain : public GameObject { private: std::vector<RainDrop> drops; public: Rain(); void draw() override; void update() override; };
#endif
