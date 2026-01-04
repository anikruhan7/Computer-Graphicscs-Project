#include "TrafficLight.h"
#include <GLUT/glut.h> // MacOS
#include <math.h>      // Required for cosf/sinf

extern bool greenLight;

void drawCircleTL(float cx, float cy, float r, int segments, float red, float green, float blue)
{
    glColor3f(red, green, blue);
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void TrafficLight::draw()
{
    glPushMatrix();

    // CHANGED: 0.95f is "Right Side" but still visible (was 1.25f)
    glTranslatef(0.95f, -0.1f, 0.0f);

    // Pole
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.015f, -0.25f);
    glVertex2f(0.015f, -0.25f);
    glVertex2f(0.015f, 0.2f);
    glVertex2f(-0.015f, 0.2f);
    glEnd();

    // Signal Box
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.045f, 0.2f);
    glVertex2f(0.045f, 0.2f);
    glVertex2f(0.045f, 0.35f);
    glVertex2f(-0.045f, 0.35f);
    glEnd();

    // Lights
    float redIntensity = greenLight ? 0.3f : 1.0f;
    float greenIntensity = greenLight ? 1.0f : 0.3f;

    drawCircleTL(0.0f, 0.31f, 0.025f, 20, redIntensity, 0.0f, 0.0f);   // Red
    drawCircleTL(0.0f, 0.24f, 0.025f, 20, 0.0f, greenIntensity, 0.0f); // Green

    glPopMatrix();
}

void TrafficLight::update() {}