#include "House.h"
using namespace std;

extern bool isDay;

House::House(float px, float py) : x(px), y(py) {}

HouseType1::HouseType1(float px, float py) : House(px, py) {}

void HouseType1::draw()
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    // Simple village house: wall
    glColor3f(0.95f, 0.87f, 0.72f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.03f);
    glVertex2f(0.3f, 0.03f);
    glVertex2f(0.3f, 0.35f);
    glVertex2f(0.0f, 0.35f);
    glEnd();

    // Roof (triangle)
    glColor3f(0.50f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.02f, 0.35f);
    glVertex2f(0.32f, 0.35f);
    glVertex2f(0.15f, 0.52f);
    glEnd();

    // Door (center-left)
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.11f, 0.03f);
    glVertex2f(0.19f, 0.03f);
    glVertex2f(0.19f, 0.18f);
    glVertex2f(0.11f, 0.18f);
    glEnd();

    // Two simple windows (left and right)
    float wr = isDay ? 0.7f : 1.0f;
    float wg = isDay ? 0.9f : 0.85f;
    float wb = isDay ? 0.8f : 0.4f;

    // left window
    glColor3f(wr, wg, wb);
    glBegin(GL_POLYGON);
    glVertex2f(0.04f, 0.18f);
    glVertex2f(0.09f, 0.18f);
    glVertex2f(0.09f, 0.24f);
    glVertex2f(0.04f, 0.24f);
    glEnd();

    // right window
    glColor3f(wr, wg, wb);
    glBegin(GL_POLYGON);
    glVertex2f(0.21f, 0.18f);
    glVertex2f(0.26f, 0.18f);
    glVertex2f(0.26f, 0.24f);
    glVertex2f(0.21f, 0.24f);
    glEnd();

    // Thin horizontal base attached to house (subtle foundation line)
    glColor3f(0.18f, 0.18f, 0.18f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.03f);
    glVertex2f(0.3f, 0.03f);
    glVertex2f(0.3f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glEnd();

    glPopMatrix();
}

HouseType2::HouseType2(float px, float py) : House(px, py) {}

void HouseType2::draw()
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    // Simple wall
    glColor3f(0.72f, 0.78f, 0.85f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.25f, 0.0f);
    glVertex2f(0.25f, 0.35f);
    glVertex2f(0.0f, 0.35f);
    glEnd();

    // Roof
    glColor3f(0.3f, 0.3f, 0.35f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.02f, 0.35f);
    glVertex2f(0.27f, 0.35f);
    glVertex2f(0.125f, 0.53f);
    glEnd();

    // Door
    glColor3f(0.45f, 0.25f, 0.10f);
    glBegin(GL_POLYGON);
    glVertex2f(0.08f, 0.0f);
    glVertex2f(0.17f, 0.0f);
    glVertex2f(0.17f, 0.18f);
    glVertex2f(0.08f, 0.18f);
    glEnd();

    // Two windows
    float wr = isDay ? 0.85f : 1.0f;
    float wg = isDay ? 0.9f : 0.85f;
    float wb = isDay ? 0.6f : 0.3f;

    glColor3f(wr, wg, wb);
    glBegin(GL_POLYGON);
    glVertex2f(0.03f, 0.22f);
    glVertex2f(0.09f, 0.22f);
    glVertex2f(0.09f, 0.28f);
    glVertex2f(0.03f, 0.28f);
    glEnd();

    glColor3f(wr, wg, wb);
    glBegin(GL_POLYGON);
    glVertex2f(0.16f, 0.22f);
    glVertex2f(0.22f, 0.22f);
    glVertex2f(0.22f, 0.28f);
    glVertex2f(0.16f, 0.28f);
    glEnd();

    // Thin horizontal base attached to house (subtle foundation line)
    glColor3f(0.3f, 0.3f, 0.35f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.25f, 0.0f);
    glVertex2f(0.25f, -0.02f);
    glVertex2f(0.0f, -0.02f);
    glEnd();

    glPopMatrix();
}