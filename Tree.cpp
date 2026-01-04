#include "Tree.h"
using namespace std;

extern bool isDay;
Tree::Tree(float px, float py, float s) : x(px), y(py), scale(s) {}

NormalTree::NormalTree(float px, float py, float s) : Tree(px, py, s) {}

void NormalTree::draw()
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(scale, scale, 1);

    float trunkR = isDay ? 0.55f : 0.3f;
    float trunkG = isDay ? 0.27f : 0.15f;
    float trunkB = isDay ? 0.07f : 0.05f;
    float leafG = isDay ? 0.6f : 0.3f;

    // Trunk
    glColor3f(trunkR, trunkG, trunkB);
    glBegin(GL_POLYGON);
    glVertex2f(-0.03f, 0.0f);
    glVertex2f(0.03f, 0.0f);
    glVertex2f(0.03f, 0.18f);
    glVertex2f(-0.03f, 0.18f);
    glEnd();

    // Leaves
    glColor3f(0.0f, leafG, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.18f, 0.18f);
    glVertex2f(0.18f, 0.18f);
    glVertex2f(0.0f, 0.45f);
    glEnd();

    glPopMatrix();
}

SlimTree::SlimTree(float px, float py, float s) : Tree(px, py, s) {}

void SlimTree::draw()
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(scale * 0.8f, scale * 1.3f, 1);

    float trunkR = isDay ? 0.50f : 0.25f;
    float trunkG = isDay ? 0.25f : 0.12f;
    float trunkB = isDay ? 0.05f : 0.02f;
    float leafG = isDay ? 0.5f : 0.25f;

    glColor3f(trunkR, trunkG, trunkB);
    glBegin(GL_POLYGON);
    glVertex2f(-0.015f, 0.0f);
    glVertex2f(0.015f, 0.0f);
    glVertex2f(0.015f, 0.15f);
    glVertex2f(-0.015f, 0.15f);
    glEnd();

    glColor3f(0.0f, leafG, 0.05f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.1f, 0.15f);
    glVertex2f(0.1f, 0.15f);
    glVertex2f(0.0f, 0.55f);
    glEnd();

    glPopMatrix();
}