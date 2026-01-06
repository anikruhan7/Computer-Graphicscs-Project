#include "Background.h"
#include <math.h>
#include <vector>
#include <cstdlib>
#include <cmath>
using namespace std;

// Initialize variables
bool isDay = true;
float cloudX = -0.8f;
float sunY = 0.75f;

// Stars for the night sky (positions, sizes and twinkle phase)
static std::vector<std::pair<float, float>> stars;
static std::vector<float> starSizes;
static float starPhase = 0.0f;

// Shooting star structure and pool
struct ShootingStar
{
    float x, y;
    float vx, vy;
    int life;
    int maxLife;
    bool active;
};
static std::vector<ShootingStar> shootingStars;
// Number of frames after startup during which shooting stars spawn frequently
static int shootingStartupFrames = 300; // ~5 seconds at 60 FPS


// Populate stars once with deterministic seed so layout is stable
static void initStars()
{
    if (!stars.empty())
        return;
    srand(12345);
    const int count = 40;
    for (int i = 0; i < count; ++i)
    {
        float x = -1.0f + 2.0f * (rand() / (float)RAND_MAX);
        float y = 0.2f + 0.8f * (rand() / (float)RAND_MAX); // upper sky region
        stars.emplace_back(x, y);
        starSizes.push_back(0.002f + 0.012f * (rand() / (float)RAND_MAX));
    }

    // Initialize shooting star pool (inactive)
    shootingStars.resize(6);
    for (auto &s : shootingStars)
    {
        s.active = false;
        s.life = 0;
        s.maxLife = 0;
        s.x = s.y = s.vx = s.vy = 0.0f;
    }
}

// Spawn a shooting star into an inactive slot
static void spawnShootingStar()
{
    if (shootingStars.empty())
        initStars();

    // Find inactive slot
    for (auto &s : shootingStars)
    {
        if (!s.active)
        {
            // start near top-right region so it crosses the sky
            float rx = 0.4f + 0.6f * (rand() / (float)RAND_MAX); // 0.4..1.0
            float ry = 0.6f + 0.4f * (rand() / (float)RAND_MAX); // 0.6..1.0
            s.x = rx;
            s.y = ry;
            s.vx = -0.008f - 0.015f * (rand() / (float)RAND_MAX); // leftwards
            s.vy = -0.004f - 0.01f * (rand() / (float)RAND_MAX);  // slightly downwards
            s.life = 0;
            s.maxLife = 40 + (int)(80 * (rand() / (float)RAND_MAX));
            s.active = true;
            break;
        }
    }
}

//  Function for draw circle
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
    // Sky Color
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

    // Sun/Moon/Clouds
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

        // Stars
        initStars();
        for (size_t i = 0; i < stars.size(); ++i)
        {
            float sx = stars[i].first;
            float sy = stars[i].second;
            float baseR = starSizes[i];
            float twinkle = 0.6f + 0.4f * (0.5f + 0.5f * sinf(starPhase * 1.5f + (float)i * 0.7f));
            float sr = baseR * (0.8f + 0.6f * twinkle);
            float brightness = 0.6f + 0.4f * twinkle;
            drawCircle(sx, sy, sr, 10, brightness, brightness, brightness);
        }

        // Shooting stars (lines that move and fade)
        for (auto &s : shootingStars)
        {
            if (!s.active)
                continue;

            float alpha = 1.0f - (s.life / (float)s.maxLife);
            // trail length depends on velocity (slightly longer for nicer look)
            float tx = s.x - s.vx * 4.0f;
            float ty = s.y - s.vy * 4.0f;

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glLineWidth(2.5f);
            // soft yellow color
            glColor4f(1.0f, 0.95f, 0.6f, 0.9f * alpha);
            glBegin(GL_LINES);
            glVertex2f(tx, ty);
            glVertex2f(s.x, s.y);
            glEnd();

            // small bright head (soft yellow)
            glPointSize(4.0f);
            glBegin(GL_POINTS);
            glColor4f(1.0f, 0.95f, 0.6f, 1.0f * alpha);
            glVertex2f(s.x, s.y);
            glEnd();

            glDisable(GL_BLEND);
        }
    }

    // Ground
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

    // POND
    glColor3f(0.2f, 0.6f, 0.9f); // Blue water
    glBegin(GL_POLYGON);
    glVertex2f(-0.95f, -0.12f); // Top-Left
    glVertex2f(-0.35f, -0.12f); // Top-Right
    glVertex2f(-0.35f, -0.39f); // Bottom-Right
    glVertex2f(-0.95f, -0.39f); // Bottom-Left
    glEnd();

    // Pond Outline
    glColor3f(0.15f, 0.5f, 0.8f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.95f, -0.12f);
    glVertex2f(-0.35f, -0.12f);
    glVertex2f(-0.35f, -0.39f);
    glVertex2f(-0.95f, -0.39f);
    glEnd();

    // ROAD
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, -0.40f);
    glVertex2f(1.0f, -0.40f);
    glVertex2f(1.0f, -0.90f);
    glVertex2f(-1.0f, -0.90f);
    glEnd();

    // ROAD LINES
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
        // Spawn more frequently during startup, then use base rate
        float baseProb = 0.006f;
        float startupProb = 0.08f; // ~8% chance per frame at startup
        float prob = (shootingStartupFrames > 0) ? startupProb : baseProb;
        if ((rand() / (float)RAND_MAX) < prob)
            spawnShootingStar();
        if (shootingStartupFrames > 0)
            shootingStartupFrames--;
    }
    else
    {
        cloudX += 0.003f;
        if (cloudX > 1.3f)
            cloudX = -1.3f;
        if (sunY < 0.85f)
            sunY += 0.0005f;
    }

    // Update shooting stars
    for (auto &s : shootingStars)
    {
        if (!s.active)
            continue;
        s.x += s.vx;
        s.y += s.vy;
        s.life++;
        if (s.life > s.maxLife || s.x < -1.2f || s.y < -0.2f)
            s.active = false;
    }

    // Progress star phase for twinkling effect
    starPhase += 0.05f;
    if (starPhase > 10000.0f)
        starPhase = 0.0f;
}