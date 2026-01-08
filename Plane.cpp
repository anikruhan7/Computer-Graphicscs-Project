#include "Plane.h"
#include <GL/glut.h>
#include <cmath>

Plane::Plane(float px, float py, float speed) : x(px), y(py), vx(speed), phase(0.0f) {}

void Plane::draw()
{
    glPushMatrix();

    // Gentle bobbing and small tilt based on phase
    float tilt = sinf(phase) * 6.0f; // degrees
    glTranslatef(x, y + sinf(phase) * 0.01f, 0.0f);
    glRotatef(tilt, 0.0f, 0.0f, 1.0f);

    // Fuselage (longer and sleeker)
    glColor3f(0.85f, 0.15f, 0.15f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.16f, -0.01f);
    glVertex2f(0.16f, -0.01f);
    glVertex2f(0.12f, 0.02f);
    glVertex2f(-0.12f, 0.02f);
    glEnd();

    // Cockpit window
    glColor3f(0.15f, 0.18f, 0.25f);
    glBegin(GL_POLYGON);
    glVertex2f(0.08f, 0.02f);
    glVertex2f(0.12f, 0.02f);
    glVertex2f(0.12f, 0.005f);
    glVertex2f(0.08f, 0.005f);
    glEnd();

    // Wings
    glColor3f(0.75f, 0.75f, 0.75f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, -0.005f);
    glVertex2f(-0.18f, -0.06f);
    glVertex2f(0.05f, -0.01f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.015f);
    glVertex2f(-0.18f, 0.06f);
    glVertex2f(0.05f, 0.01f);
    glEnd();

    // Tail assembly
    glColor3f(0.85f, 0.15f, 0.15f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.16f, 0.02f);
    glVertex2f(-0.22f, 0.06f);
    glVertex2f(-0.12f, 0.02f);
    glEnd();

    // Window row
    glColor3f(0.15f, 0.18f, 0.25f);
    for (int i = 0; i < 4; ++i)
    {
        float wx = -0.02f + i * 0.06f;
        glBegin(GL_POLYGON);
        glVertex2f(wx, 0.005f);
        glVertex2f(wx + 0.03f, 0.005f);
        glVertex2f(wx + 0.03f, -0.005f);
        glVertex2f(wx, -0.005f);
        glEnd();
    }

    // Contrail (faint, behind plane)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 1.0f, 1.0f, 0.22f);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < 8; ++i)
    {
        float tx = x - i * 0.06f;
        float ty = y + sinf(phase - i * 0.2f) * 0.007f;
        glVertex2f(tx, ty);
    }
    glEnd();
    glDisable(GL_BLEND);

    glPopMatrix();
}

void Plane::update()
{
    x += vx;
    phase += 0.08f;
    if (x > 1.6f)
        x = -1.6f;
}
