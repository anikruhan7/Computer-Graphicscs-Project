#include "CityBackground.h"
#include "Background.h" // for isDay
#include <GL/glut.h>
#include <cmath>

// Globals used by ships/other objects
float cityWaterPhase = 0.0f;
float cityWaterSurfaceY = -0.64f; // centerline for reflections

// Clouds and sun/moon
static float cityCloudX = -0.8f;
static float citySunY = 0.75f;
// 0.0 = day, 1.0 = night (smooth blend)
static float cityNightBlend = 0.0f;

// helper for circles
static void drawCircle(float cx, float cy, float r, int segments, float red, float green, float blue)
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
// Simple city background: sky, a river strip, road strip, and distant silhouette

void drawRect(float x1, float y1, float x2, float y2, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

void CityBackground::draw()
{
    // Sky (blend day <-> night using cityNightBlend)
    float dayR = 0.45f, dayG = 0.70f, dayB = 0.95f;
    float nightR = 0.03f, nightG = 0.05f, nightB = 0.12f;
    float nb = cityNightBlend; // 0..1
    float rSky = dayR * (1.0f - nb) + nightR * nb;
    float gSky = dayG * (1.0f - nb) + nightG * nb;
    float bSky = dayB * (1.0f - nb) + nightB * nb;

    glColor3f(rSky, gSky, bSky);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(1.0f, -0.1f);
    glVertex2f(-1.0f, -0.1f);
    glEnd();

    // Subtle stars appear as night falls
    if (cityNightBlend > 0.15f)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1.0f, 1.0f, 1.0f, 0.7f * cityNightBlend);
        glPointSize(2.0f);
        glBegin(GL_POINTS);
        glVertex2f(-0.6f, 0.92f);
        glVertex2f(-0.2f, 0.86f);
        glVertex2f(0.0f, 0.94f);
        glVertex2f(0.34f, 0.88f);
        glVertex2f(0.75f, 0.98f);
        glEnd();
        glDisable(GL_BLEND);
    }

    // Distant city silhouette (subtle)
    for (float x = -1.05f; x < 1.05f; x += 0.12f)
    {
        float bw = 0.09f;
        float bh = 0.18f + (int((x + 1.0f) * 10) % 4) * 0.12f;
        float left = x + 0.01f;
        drawRect(left, -0.1f, left + bw, -0.1f + bh, 0.15f, 0.15f, 0.18f);
    }

    // Ground under buildings (replaces river directly under buildings)
    // Extended down to touch the river so there's no visible gap
    drawRect(-1.0f, -0.20f, 1.0f, -0.56f, 0.18f, 0.45f, 0.12f);

    // Day/Night Sun / Moon & Clouds
    if (isDay)
    {
        // Sun
        drawCircle(0.6f, citySunY, 0.09f, 40, 1.0f, 0.84f, 0.0f);
        // Clouds
        glColor3f(1.0f, 1.0f, 1.0f);
        drawCircle(cityCloudX, 0.75f, 0.08f, 30, 1, 1, 1);
        drawCircle(cityCloudX - 0.09f, 0.73f, 0.07f, 30, 1, 1, 1);
        drawCircle(cityCloudX + 0.09f, 0.73f, 0.07f, 30, 1, 1, 1);
    }
    else
    {
        // Moon
        drawCircle(0.6f, citySunY, 0.07f, 40, 0.9f, 0.9f, 0.95f);
    }

    // Soft bank between ground and river (sloped transition for visual smoothing)
    glColor3f(0.16f, 0.40f, 0.10f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-1.0f, -0.56f);
    glVertex2f(-0.3f, -0.48f);
    glVertex2f(0.0f, -0.56f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.16f, 0.36f, 0.09f);
    glVertex2f(0.0f, -0.56f);
    glVertex2f(0.3f, -0.48f);
    glVertex2f(1.0f, -0.56f);
    glEnd();

    // Lower river — separated from buildings, where ships sail
    drawRect(-1.0f, -0.56f, 1.0f, -0.72f, 0.12f, 0.6f, 0.9f);

    // Extended water connecting river to road
    drawRect(-1.0f, -0.72f, 1.0f, -0.84f, 0.12f, 0.6f, 0.9f);

    // Water highlights / waves (simple sin-based lines)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 1.0f, 1.0f, 0.12f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
    for (float x = -1.0f; x <= 1.0f; x += 0.08f)
    {
        float wobble = 0.01f * sinf((x * 6.0f) + cityWaterPhase * 2.0f);
        float wy = -0.62f + wobble; // slightly below the top of river
        glVertex2f(x, wy);
        glVertex2f(x + 0.06f, wy + 0.005f);
    }
    glEnd();
    glDisable(GL_BLEND);

    // Advance clouds and sun while respecting day/night
    if (isDay)
    {
        cityCloudX += 0.003f;
        if (cityCloudX > 1.3f)
            cityCloudX = -1.3f;
        if (citySunY < 0.85f)
            citySunY += 0.0005f;
    }
    else
    {
        // night - moon might slightly sink
        if (citySunY > 0.6f)
            citySunY -= 0.0001f;
    }
    // Road below river moved up to reduce gap and align better with river bottom
    drawRect(-1.0f, -0.84f, 1.0f, -1.0f, 0.25f, 0.25f, 0.25f);

    // Road divider lines (moved up accordingly)
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    for (float x = -1.0f; x < 1.0f; x += 0.13f)
    {
        glVertex2f(x, -0.94f);
        glVertex2f(x + 0.07f, -0.94f);
    }
    glEnd();
}

void CityBackground::update()
{
    // Animate water phase for waves and reflections
    cityWaterPhase += 0.03f;
    if (cityWaterPhase > 10000.0f)
        cityWaterPhase = 0.0f;

    // Smooth day/night transition (cityNightBlend approaches 1.0 at night)
    if (!isDay)
        cityNightBlend += 0.01f;
    else
        cityNightBlend -= 0.01f;

    if (cityNightBlend < 0.0f)
        cityNightBlend = 0.0f;
    if (cityNightBlend > 1.0f)
        cityNightBlend = 1.0f;
}
