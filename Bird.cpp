#include "Bird.h"
#include <math.h>

extern bool isDay; // birds to appear during the day

Bird::Bird(float startX, float startY, float s)
    : x(startX), y(startY), speed(s) {}

void Bird::draw()
{
    if (!isDay)
        return; // Hide birds at night

    glColor3f(0.0f, 0.0f, 0.0f); // Black color
    glLineWidth(2.0f);

    glBegin(GL_LINES);
    // Left Wing
    glVertex2f(x - 0.03f, y + 0.03f);
    glVertex2f(x, y);

    // Right Wing
    glVertex2f(x, y);
    glVertex2f(x + 0.03f, y + 0.03f);
    glEnd();
}

void Bird::update()
{
    if (!isDay)
        return;

    x += speed;

    // Reset position when it flies off screen
    if (x > 1.2f)
    {
        x = -1.2f;
    }
}