#define GL_SILENCE_DEPRECATION
#include "Rain.hpp"
#include <cstdlib>
#include <math.h>
#include <GLUT/glut.h>
extern bool isRaining; extern bool isDay;
Rain::Rain() {
    for (int i = 0; i < 400; i++) {
        RainDrop d; d.x = (rand()/(float)RAND_MAX)*3.0f-1.5f; d.y = (rand()/(float)RAND_MAX)*2.0f-1.0f;
        d.speed = 0.03f+(rand()/(float)RAND_MAX)*0.02f; d.length = 0.05f+(rand()/(float)RAND_MAX)*0.03f;
        drops.push_back(d);
    }
}
void Rain::draw() {
    if (!isRaining) return;
    if (isDay) glColor3f(0.7f, 0.7f, 0.8f); else glColor3f(0.4f, 0.4f, 0.5f);
    glLineWidth(1.0f); glBegin(GL_LINES);
    for (const auto& d : drops) { glVertex2f(d.x, d.y); glVertex2f(d.x - 0.01f, d.y - d.length); }
    glEnd();
}
void Rain::update() {
    if (!isRaining) return;
    for (auto& d : drops) { d.y -= d.speed; d.x -= 0.005f; if (d.y < -1.0f) { d.y = 1.0f; d.x = (rand()/(float)RAND_MAX)*3.0f-1.5f; } }
}

