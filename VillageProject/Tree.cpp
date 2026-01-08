#define GL_SILENCE_DEPRECATION

#include "Tree.hpp"
#include <GLUT/glut.h>
#include <math.h>

extern bool isDay; extern bool isRaining;

Tree::Tree(float px, float py, float s) : x(px), y(py), scale(s) {}

void drawLeafCircle(float cx, float cy, float r) {
    glBegin(GL_POLYGON); for(int i=0; i<20; i++) { float theta = 2.0f * 3.14159f * i / 20.0f; glVertex2f(cx + r * cosf(theta), cy + r * sinf(theta)); } glEnd();
}

NormalTree::NormalTree(float px, float py, float s) : Tree(px, py, s) {}

void NormalTree::draw() {
    float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f; float wind = isRaining ? 0.04f : 0.005f; float sway = sinf(time * 2.5f + x) * wind;
    glPushMatrix(); glTranslatef(x, y, 0); glScalef(scale, scale, 1);
    
    // Trunk
    float trunkR = isDay ? 0.4f : 0.2f; glColor3f(trunkR, isDay?0.2f:0.1f, isDay?0.05f:0.02f);
    glBegin(GL_POLYGON); glVertex2f(-0.04f, 0.0f); glVertex2f(0.04f, 0.0f); glVertex2f(0.02f + sway*0.2f, 0.25f); glVertex2f(-0.02f + sway*0.2f, 0.25f); glEnd();
    
    // Leaves (Rich Green)
    float leafG = isDay ? 0.6f : 0.25f; glColor3f(0.1f, leafG, 0.1f);
    drawLeafCircle(-0.12f + sway, 0.25f, 0.12f); drawLeafCircle(0.12f + sway, 0.28f, 0.11f);
    drawLeafCircle(0.0f + sway * 1.5f, 0.38f, 0.14f); drawLeafCircle(0.0f + sway, 0.25f, 0.15f);
    glPopMatrix();
}

SlimTree::SlimTree(float px, float py, float s) : Tree(px, py, s) {}

void SlimTree::draw() {
    float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f; float wind = isRaining ? 0.05f : 0.008f; float sway = cosf(time * 3.0f + x) * wind;
    glPushMatrix(); glTranslatef(x, y, 0); glScalef(scale, scale, 1);
    
    // Trunk
    float trunkR = isDay ? 0.35f : 0.15f; glColor3f(trunkR, trunkR*0.5f, 0.05f);
    glBegin(GL_POLYGON); glVertex2f(-0.02f, 0.0f); glVertex2f(0.02f, 0.0f); glVertex2f(0.01f + sway*0.2f, 0.20f); glVertex2f(-0.01f + sway*0.2f, 0.20f); glEnd();
    
    // Leaves (Pine Green)
    float leafG = isDay ? 0.5f : 0.2f;
    glColor3f(0.05f, leafG, 0.05f); glBegin(GL_TRIANGLES); glVertex2f(-0.15f + sway, 0.15f); glVertex2f(0.15f + sway, 0.15f); glVertex2f(0.0f + sway, 0.35f); glEnd();
    glColor3f(0.05f, leafG + 0.08f, 0.05f); glBegin(GL_TRIANGLES); glVertex2f(-0.12f + sway * 1.2f, 0.30f); glVertex2f(0.12f + sway * 1.2f, 0.30f); glVertex2f(0.0f + sway * 1.2f, 0.50f); glEnd();
    glColor3f(0.05f, leafG + 0.15f, 0.05f); glBegin(GL_TRIANGLES); glVertex2f(-0.08f + sway * 1.5f, 0.45f); glVertex2f(0.08f + sway * 1.5f, 0.45f); glVertex2f(0.0f + sway * 2.0f, 0.60f); glEnd();
    glPopMatrix();
}
