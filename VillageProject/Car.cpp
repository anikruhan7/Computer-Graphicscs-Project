#define GL_SILENCE_DEPRECATION

#include "Car.hpp"
#include <math.h>
#include <GLUT/glut.h>
extern bool isMoving; extern bool greenLight; extern bool isDay;
Car::Car(float startX, float startY, float red, float green, float blue, float dir) : x(startX), y(startY), r(red), g(green), b(blue), direction(dir) {}
void Car::draw() {
    glColor3f(r, g, b); glBegin(GL_POLYGON); glVertex2f(x, y); glVertex2f(x+0.26, y); glVertex2f(x+0.26, y+0.07); glVertex2f(x, y+0.07); glEnd();
    glColor3f(r, g, b); glBegin(GL_POLYGON); glVertex2f(x+0.05, y+0.07); glVertex2f(x+0.21, y+0.07); glVertex2f(x+0.18, y+0.13); glVertex2f(x+0.08, y+0.13); glEnd();
    glColor3f(0.7f, 0.9f, 1.0f); glBegin(GL_POLYGON); glVertex2f(x+0.06, y+0.075); glVertex2f(x+0.12, y+0.075); glVertex2f(x+0.12, y+0.12); glVertex2f(x+0.085, y+0.12); glEnd();
    glBegin(GL_POLYGON); glVertex2f(x+0.14, y+0.075); glVertex2f(x+0.20, y+0.075); glVertex2f(x+0.175, y+0.12); glVertex2f(x+0.14, y+0.12); glEnd();
    glColor3f(0.1,0.1,0.1); glBegin(GL_POLYGON); for(int i=0;i<20;i++) glVertex2f((x+0.06)+0.035*cos(i*6.28/20), y+0.035*sin(i*6.28/20)); glEnd();
    glBegin(GL_POLYGON); for(int i=0;i<20;i++) glVertex2f((x+0.20)+0.035*cos(i*6.28/20), y+0.035*sin(i*6.28/20)); glEnd();
    bool lights = !isDay;
    if(direction > 0) {
        if(lights) { glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); glColor4f(1,1,0.8,0.4); glBegin(GL_TRIANGLES); glVertex2f(x+0.26, y+0.05); glVertex2f(x+0.6, y+0.08); glVertex2f(x+0.6, y-0.05); glEnd(); glDisable(GL_BLEND); glColor3f(1,1,0.5); } else { glColor3f(0.8,0.8,0); }
        glBegin(GL_POLYGON); glVertex2f(x+0.25,y+0.04); glVertex2f(x+0.265,y+0.04); glVertex2f(x+0.265,y+0.06); glVertex2f(x+0.25,y+0.06); glEnd();
        glColor3f(lights?1:0.6,0,0); glBegin(GL_POLYGON); glVertex2f(x-0.005,y+0.04); glVertex2f(x+0.01,y+0.04); glVertex2f(x+0.01,y+0.06); glVertex2f(x-0.005,y+0.06); glEnd();
    } else {
        if(lights) { glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); glColor4f(1,1,0.8,0.4); glBegin(GL_TRIANGLES); glVertex2f(x, y+0.05); glVertex2f(x-0.35, y+0.08); glVertex2f(x-0.35, y-0.05); glEnd(); glDisable(GL_BLEND); glColor3f(1,1,0.5); } else { glColor3f(0.8,0.8,0); }
        glBegin(GL_POLYGON); glVertex2f(x-0.005,y+0.04); glVertex2f(x+0.01,y+0.04); glVertex2f(x+0.01,y+0.06); glVertex2f(x-0.005,y+0.06); glEnd();
        glColor3f(lights?1:0.6,0,0); glBegin(GL_POLYGON); glVertex2f(x+0.25,y+0.04); glVertex2f(x+0.265,y+0.04); glVertex2f(x+0.265,y+0.06); glVertex2f(x+0.25,y+0.06); glEnd();
    }
}
void Car::update() { if (!isMoving || !greenLight) return; x += direction * 0.008f; if (x > 1.3f) x = -1.3f; if (x < -1.3f) x = 1.3f; }
