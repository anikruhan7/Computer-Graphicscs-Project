#define GL_SILENCE_DEPRECATION
#include "TrafficLight.hpp"
#include <GLUT/glut.h>
#include <math.h>
extern bool greenLight;
void TrafficLight::draw() {
    glPushMatrix(); glTranslatef(0.95f, -0.1f, 0.0f);
    glColor3f(0.2f, 0.2f, 0.2f); glBegin(GL_POLYGON); glVertex2f(-0.015, -0.25); glVertex2f(0.015, -0.25); glVertex2f(0.015, 0.2); glVertex2f(-0.015, 0.2); glEnd();
    glColor3f(0.1f, 0.1f, 0.1f); glBegin(GL_POLYGON); glVertex2f(-0.045, 0.2); glVertex2f(0.045, 0.2); glVertex2f(0.045, 0.35); glVertex2f(-0.045, 0.35); glEnd();
    float rI = greenLight ? 0.3f : 1.0f; float gI = greenLight ? 1.0f : 0.3f;
    glColor3f(rI, 0, 0); glBegin(GL_POLYGON); for(int i=0;i<20;i++) glVertex2f(0+0.025*cos(i*6.28/20), 0.31+0.025*sin(i*6.28/20)); glEnd();
    glColor3f(0, gI, 0); glBegin(GL_POLYGON); for(int i=0;i<20;i++) glVertex2f(0+0.025*cos(i*6.28/20), 0.24+0.025*sin(i*6.28/20)); glEnd();
    glPopMatrix();
}
