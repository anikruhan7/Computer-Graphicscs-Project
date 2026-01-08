#include "Car.h"
#include "Background.h"
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

    // Night lights: headlights and taillights when it's night
    if (!isDay)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Headlight (yellow) - triangle projecting forward a bit
        glColor4f(1.0f, 0.95f, 0.6f, 0.95f);
        glBegin(GL_TRIANGLES);
        if (direction > 0)
        {
            glVertex2f(x + 0.25f, y + 0.05f);
            glVertex2f(x + 0.45f, y + 0.02f);
            glVertex2f(x + 0.45f, y + 0.08f);
        }
        else
        {
            glVertex2f(x, y + 0.05f);
            glVertex2f(x - 0.20f, y + 0.02f);
            glVertex2f(x - 0.20f, y + 0.08f);
        }
        glEnd();

        // Soft beam on road (very faint)
        glColor4f(1.0f, 0.95f, 0.6f, 0.15f);
        glBegin(GL_TRIANGLES);
        if (direction > 0)
        {
            glVertex2f(x + 0.30f, y + 0.03f);
            glVertex2f(x + 0.85f, -0.94f);
            glVertex2f(x + 0.30f, -0.94f);
        }
        else
        {
            glVertex2f(x - 0.05f, y + 0.03f);
            glVertex2f(x - 0.60f, -0.94f);
            glVertex2f(x - 0.05f, -0.94f);
        }
        glEnd();

        // Taillights (red)
        glColor4f(0.9f, 0.12f, 0.12f, 1.0f);
        glBegin(GL_POLYGON);
        if (direction > 0)
        {
            glVertex2f(x - 0.01f, y + 0.01f);
            glVertex2f(x + 0.02f, y + 0.01f);
            glVertex2f(x + 0.02f, y + 0.04f);
            glVertex2f(x - 0.01f, y + 0.04f);
        }
        else
        {
            glVertex2f(x + 0.23f, y + 0.01f);
            glVertex2f(x + 0.26f, y + 0.01f);
            glVertex2f(x + 0.26f, y + 0.04f);
            glVertex2f(x + 0.23f, y + 0.04f);
        }
        glEnd();

        glDisable(GL_BLEND);
    }
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