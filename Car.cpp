#include "Car.h"
#include <math.h>
using namespace std;
extern bool isMoving;
extern bool greenLight;
const float speed = 0.008f;

Car::Car(float startX, float startY, float red, float green, float blue, float dir)
    : x(startX), y(startY), r(red), g(green), b(blue), direction(dir) {}

void Car::draw()
{
    // Car body
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + 0.25f, y);
    glVertex2f(x + 0.25f, y + 0.08f);
    glVertex2f(x, y + 0.08f);
    glEnd();

    // Roof
    glColor3f(r * 0.8f, g * 0.8f, b * 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(x + 0.05f, y + 0.08f);
    glVertex2f(x + 0.20f, y + 0.08f);
    glVertex2f(x + 0.18f, y + 0.14f);
    glVertex2f(x + 0.07f, y + 0.14f);
    glEnd();

    // Wheels
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 20; i++)
    {
        float theta = 2.0f * 3.1415926f * i / 20;
        glVertex2f(x + 0.06f + 0.035f * cosf(theta), y + 0.035f * sinf(theta));
    }
    glEnd();
    glBegin(GL_POLYGON);
    for (int i = 0; i < 20; i++)
    {
        float theta = 2.0f * 3.1415926f * i / 20;
        glVertex2f(x + 0.19f + 0.035f * cosf(theta), y + 0.035f * sinf(theta));
    }
    glEnd();

    // Wheel Hubs
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 20; i++)
    {
        float theta = 2.0f * 3.1415926f * i / 20;
        glVertex2f(x + 0.06f + 0.015f * cosf(theta), y + 0.015f * sinf(theta));
    }
    glEnd();
    glBegin(GL_POLYGON);
    for (int i = 0; i < 20; i++)
    {
        float theta = 2.0f * 3.1415926f * i / 20;
        glVertex2f(x + 0.19f + 0.015f * cosf(theta), y + 0.015f * sinf(theta));
    }
    glEnd();
}

void Car::update()
{
    if (!isMoving || !greenLight)
        return;

    x += direction * speed;

    if (x > 1.3f)
        x = -1.3f;
    if (x < -1.3f)
        x = 1.3f;
}