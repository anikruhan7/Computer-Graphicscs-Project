#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "GameObject.h"
#include <vector>
using namespace std ;
// Global externs
extern bool isDay;
extern float cloudX;
extern float sunY;

struct Star { float x, y, alpha; };
struct SunRay { float angle, length, width, speed; };

class Background : public GameObject {
private:
    vector<Star> stars;
    vector<SunRay> rays;
public:
    Background();
    void draw() override;
    void update() override;
};
#endif
