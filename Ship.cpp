#include "Ship.h"
#include <GL/glut.h>

Ship::Ship(float px, float py, float speed, float s) : x(px), y(py), vx(speed), scale(s) {}

// Helper to draw the ship body scaled and centered at origin
static void drawShipShape(float scale)
{
    // Hull
    glBegin(GL_POLYGON);
    glVertex2f(-0.2f * scale, -0.03f * scale);
    glVertex2f(0.2f * scale, -0.03f * scale);
    glVertex2f(0.12f * scale, 0.03f * scale);
    glVertex2f(-0.12f * scale, 0.03f * scale);
    glEnd();

    // Deck cabin
    glBegin(GL_POLYGON);
    glVertex2f(-0.07f * scale, 0.03f * scale);
    glVertex2f(0.07f * scale, 0.03f * scale);
    glVertex2f(0.06f * scale, 0.07f * scale);
    glVertex2f(-0.06f * scale, 0.07f * scale);
    glEnd();

    // Mast
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.07f * scale);
    glVertex2f(0.02f * scale, 0.07f * scale);
    glVertex2f(0.02f * scale, 0.14f * scale);
    glVertex2f(0.0f, 0.14f * scale);
    glEnd();
}

void Ship::draw()
{
    // Normal ship (no reflection)
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    glColor3f(0.2f, 0.12f, 0.08f);
    drawShipShape(scale);

    // Deck cabin
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.07f * scale, 0.03f * scale);
    glVertex2f(0.07f * scale, 0.03f * scale);
    glVertex2f(0.06f * scale, 0.07f * scale);
    glVertex2f(-0.06f * scale, 0.07f * scale);
    glEnd();

    // Flag
    glColor3f(0.9f, 0.1f, 0.1f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.02f * scale, 0.13f * scale);
    glVertex2f(0.08f * scale, 0.11f * scale);
    glVertex2f(0.02f * scale, 0.10f * scale);
    glEnd();

    // White wake lines to show it's on water
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(-0.25f * scale, -0.04f * scale);
    glVertex2f(-0.18f * scale, -0.06f * scale);
    glVertex2f(0.25f * scale, -0.04f * scale);
    glVertex2f(0.18f * scale, -0.06f * scale);
    glEnd();

    glPopMatrix();
}

void Ship::update()
{
    x += vx;

    if (x > 1.3f)
        x = -1.3f;
    if (x < -1.3f)
        x = 1.3f;
}