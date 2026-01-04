#include "Bus.h"
#include <math.h>

extern bool isMoving;
extern bool greenLight;

Bus::Bus(float startX, float startY, float dir)
    : x(startX), y(startY), direction(dir)
{
    speed = 0.005f; // Buses are slower than cars
}

void Bus::draw()
{
    // Bus Body (Yellow)
    glColor3f(1.0f, 0.8f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + 0.45f, y);         // Longer than car
    glVertex2f(x + 0.45f, y + 0.15f); // Taller than car
    glVertex2f(x, y + 0.15f);
    glEnd();

    // Windows (Blue strips)
    glColor3f(0.3f, 0.7f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(x + 0.02f, y + 0.08f);
    glVertex2f(x + 0.43f, y + 0.08f);
    glVertex2f(x + 0.43f, y + 0.13f);
    glVertex2f(x + 0.02f, y + 0.13f);
    glEnd();

    // Wheels (3 wheels for bus)
    glColor3f(0.0f, 0.0f, 0.0f);
    float wheelY = y;
    float wheelOffsets[] = {0.08f, 0.22f, 0.36f};

    for (int w = 0; w < 3; w++)
    {
        glBegin(GL_POLYGON);
        for (int i = 0; i < 20; i++)
        {
            float theta = 2.0f * 3.1415926f * i / 20;
            glVertex2f((x + wheelOffsets[w]) + 0.035f * cosf(theta), wheelY + 0.035f * sinf(theta));
        }
        glEnd();
    }
}

void Bus::update()
{
    if (!isMoving || !greenLight)
        return;

    x += direction * speed;

    if (x > 1.4f)
        x = -1.4f;
    if (x < -1.4f)
        x = 1.4f;
}