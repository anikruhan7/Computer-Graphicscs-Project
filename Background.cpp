#include "Background.h"
#include <math.h>

using namespace std;

// Initialize variables
bool isDay = true;
float cloudX = -0.8f;
float sunY = 0.75f;

// Helper function to draw circles
void drawCircle(float cx, float cy, float r, int segments, float red, float green, float blue)
{
    glColor3f(red, green, blue);
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void Background::draw()
{
    // 1. Sky Color
    if (isDay)
        glColor3f(0.53f, 0.81f, 0.98f);
    else
        glColor3f(0.05f, 0.05f, 0.2f);

    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(1.0f, -0.2f);
    glVertex2f(-1.0f, -0.2f);
    glEnd();

    // 2. Sun/Moon/Clouds
    if (isDay)
    {
        drawCircle(0.0f, sunY, 0.1f, 50, 1.0f, 0.84f, 0.0f); // Sun
        // Clouds
        glColor3f(1.0f, 1.0f, 1.0f);
        drawCircle(cloudX, 0.75f, 0.08f, 30, 1, 1, 1);
        drawCircle(cloudX - 0.09f, 0.73f, 0.07f, 30, 1, 1, 1);
        drawCircle(cloudX + 0.09f, 0.73f, 0.07f, 30, 1, 1, 1);
    }
    else
    {
        drawCircle(0.0f, 0.75f, 0.1f, 40, 0.9f, 0.9f, 0.9f); // Moon
        drawCircle(0.04f, 0.77f, 0.1f, 40, 0.05f, 0.05f, 0.2f);
    }

    // 3. Ground
    glColor3f(0.0f, 0.55f, 0.0f); // Green Color
    glBegin(GL_POLYGON);

    // Top Left point (Controls the height)
    glVertex2f(-1.0f, -0.1f);

    // Top Right point (Controls the height)
    glVertex2f(1.0f, -0.1f);

    // Bottom Right
    glVertex2f(1.0f, -1.0f);

    // Bottom Left
    glVertex2f(-1.0f, -1.0f);

    glEnd();

    // --- POND (EXTENDED UPPER) ---
    glColor3f(0.2f, 0.6f, 0.9f); // Blue water
    glBegin(GL_POLYGON);

    // CHANGED: Top Y moved up from -0.22f to -0.12f
    glVertex2f(-0.95f, -0.12f); // Top-Left
    glVertex2f(-0.35f, -0.12f); // Top-Right

    glVertex2f(-0.35f, -0.39f); // Bottom-Right
    glVertex2f(-0.95f, -0.39f); // Bottom-Left
    glEnd();

    // Pond Outline
    glColor3f(0.15f, 0.5f, 0.8f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    // CHANGED: Top Y moved up here too
    glVertex2f(-0.95f, -0.12f);
    glVertex2f(-0.35f, -0.12f);
    glVertex2f(-0.35f, -0.39f);
    glVertex2f(-0.95f, -0.39f);
    glEnd();

    // 4. Road
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, -0.40f);
    glVertex2f(1.0f, -0.40f);
    glVertex2f(1.0f, -0.90f);
    glVertex2f(-1.0f, -0.90f);
    glEnd();

    // --- RESTORED ROAD LINES ---
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    for (float x = -1.0f; x < 1.0f; x += 0.25f)
    {
        glVertex2f(x, -0.65f);
        glVertex2f(x + 0.14f, -0.65f);
    }
    glEnd();
}

void Background::update()
{
    if (!isDay)
    {
        sunY = 0.5f;
        return;
    }
    cloudX += 0.003f;
    if (cloudX > 1.3f)
        cloudX = -1.3f;
    if (sunY < 0.85f)
        sunY += 0.0005f;
}