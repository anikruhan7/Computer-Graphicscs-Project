#include "Building.h"
#include "Background.h" // for isDay
#include <GL/glut.h>
#include <algorithm>

Building::Building(float px, float py, float pw, float ph, float red, float green, float blue)
    : x(px), y(py), w(pw), h(ph), r(red), g(green), b(blue)
{
}

void Building::draw()
{
    // Body
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    glVertex2f(x - w / 2.0f, y);
    glVertex2f(x + w / 2.0f, y);
    glVertex2f(x + w / 2.0f, y + h);
    glVertex2f(x - w / 2.0f, y + h);
    glEnd();

    // Decorative vertical stripes for variation
    glColor3f(r * 0.85f, g * 0.85f, b * 0.85f);
    float stripeW = w * 0.12f;
    for (int s = 0; s < 2; ++s)
    {
        float sx = x - w / 2.0f + 0.08f + s * (w - 0.16f);
        glBegin(GL_POLYGON);
        glVertex2f(sx, y + 0.04f);
        glVertex2f(sx + stripeW, y + 0.04f);
        glVertex2f(sx + stripeW, y + h - 0.02f);
        glVertex2f(sx, y + h - 0.02f);
        glEnd();
    }

    // Rooftop parapet
    glColor3f(r * 0.9f, g * 0.9f, b * 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(x - w / 2.0f, y + h);
    glVertex2f(x + w / 2.0f, y + h);
    glVertex2f(x + w / 2.0f, y + h + 0.02f);
    glVertex2f(x - w / 2.0f, y + h + 0.02f);
    glEnd();

    // Windows pattern with some windows lit (for visual interest)
    float wx = x - w / 2.0f + 0.03f;
    float wy = y + 0.06f;
    int rows = std::max(3, (int)(h / 0.05f));
    int cols = 3;
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            float sx = wx + col * (w / cols - 0.03f);
            float sy = wy + row * 0.05f;

            // Decide whether this window is lit — deterministic based on position
            int key = (int)((x + 1.0f) * 1000) + row * 7 + col * 13;
            bool lit = (key % 4 == 0);

            // If it's day, windows appear dark; at night some windows glow
            if (!isDay && lit)
                glColor3f(1.0f, 0.9f, 0.4f);
            else
                glColor3f(0.06f, 0.06f, 0.07f);

            glBegin(GL_POLYGON);
            glVertex2f(sx, sy);
            glVertex2f(sx + 0.045f, sy);
            glVertex2f(sx + 0.045f, sy + 0.035f);
            glVertex2f(sx, sy + 0.035f);
            glEnd();
        }
    }

    // Small antenna or water tank on rooftop
    glColor3f(0.12f, 0.12f, 0.12f);
    glBegin(GL_POLYGON);
    glVertex2f(x + w * 0.18f, y + h + 0.02f);
    glVertex2f(x + w * 0.26f, y + h + 0.02f);
    glVertex2f(x + w * 0.26f, y + h + 0.06f);
    glVertex2f(x + w * 0.18f, y + h + 0.06f);
    glEnd();
}