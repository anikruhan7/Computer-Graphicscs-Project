#define GL_SILENCE_DEPRECATION

#include "Bird.hpp"
#include <math.h>
#include <GLUT/glut.h>
#include <cstdlib>
extern bool isDay;
extern bool isRaining;
Bird::Bird(float startX, float startY, float s) : x(startX), y(startY), speed(s), wingAngle(0.0f) {}
void Bird::draw() {
    if (!isDay || isRaining) return; // Hide birds at night/rain
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(0.5f, 0.5f, 1.0f);
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_POLYGON);
    for(int i=0; i<360; i+=20) glVertex2f(0.04f*cosf(i*3.14/180), 0.02f*sinf(i*3.14/180));
    glEnd();
    glBegin(GL_POLYGON);
    for(int i=0; i<360; i+=20) glVertex2f(0.05f+0.015f*cosf(i*3.14/180), 0.015f+0.015f*sinf(i*3.14/180)); glEnd();
    float flap = sinf(wingAngle) * 0.05f; glBegin(GL_TRIANGLES);
    glVertex2f(-0.02f, 0.0f);
    glVertex2f(0.02f, 0.0f);
    glVertex2f(0.0f, 0.05f + flap);
    glEnd();
    glPopMatrix();
}
void Bird::update()
{ if (!isDay || isRaining) return;
    x += speed;
    wingAngle += 0.5f;
    if (x > 1.2f)
    {
        x = -1.2f;
        y = 0.6f + (rand() / (float)RAND_MAX) * 0.3f;
    }
}
