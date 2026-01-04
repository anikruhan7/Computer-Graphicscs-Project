#include "House.h"
using namespace std;

House::House(float px, float py) : x(px), y(py) {}

HouseType1::HouseType1(float px, float py) : House(px, py) {}

void HouseType1::draw()
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    glColor3f(0.25f, 0.25f, 0.25f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.3f, 0.0f);
    glVertex2f(0.3f, 0.03f);
    glVertex2f(0.0f, 0.03f);
    glEnd();

    glColor3f(0.95f, 0.87f, 0.72f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.03f);
    glVertex2f(0.3f, 0.03f);
    glVertex2f(0.3f, 0.35f);
    glVertex2f(0.0f, 0.35f);
    glEnd();

    glColor3f(0.50f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.05f, 0.35f);
    glVertex2f(0.35f, 0.35f);
    glVertex2f(0.15f, 0.55f);
    glEnd();

    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.12f, 0.03f);
    glVertex2f(0.18f, 0.03f);
    glVertex2f(0.18f, 0.18f);
    glVertex2f(0.12f, 0.18f);
    glEnd();

    glColor3f(0.3f, 0.5f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.04f, 0.15f);
    glVertex2f(0.09f, 0.15f);
    glVertex2f(0.09f, 0.25f);
    glVertex2f(0.04f, 0.25f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.21f, 0.15f);
    glVertex2f(0.26f, 0.15f);
    glVertex2f(0.26f, 0.25f);
    glVertex2f(0.21f, 0.25f);
    glEnd();

    glPopMatrix();
}

HouseType2::HouseType2(float px, float py) : House(px, py) {}

void HouseType2::draw()
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    glColor3f(0.7f, 0.75f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.25f, 0.0f);
    glVertex2f(0.25f, 0.35f);
    glVertex2f(0.0f, 0.35f);
    glEnd();

    glColor3f(0.3f, 0.3f, 0.35f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.02f, 0.35f);
    glVertex2f(0.27f, 0.35f);
    glVertex2f(0.125f, 0.55f);
    glEnd();

    glColor3f(0.45f, 0.25f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(0.08f, 0.0f);
    glVertex2f(0.17f, 0.0f);
    glVertex2f(0.17f, 0.18f);
    glVertex2f(0.08f, 0.18f);
    glEnd();

    glColor3f(0.9f, 0.9f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(0.03f, 0.22f);
    glVertex2f(0.09f, 0.22f);
    glVertex2f(0.09f, 0.28f);
    glVertex2f(0.03f, 0.28f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.16f, 0.22f);
    glVertex2f(0.22f, 0.22f);
    glVertex2f(0.22f, 0.28f);
    glVertex2f(0.16f, 0.28f);
    glEnd();

    glPopMatrix();
}