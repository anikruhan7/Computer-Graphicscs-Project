#define GL_SILENCE_DEPRECATION

#include "Background.hpp"
#include <math.h>
#include <cstdlib>
#include <GLUT/glut.h>

using namespace std;

// --- GLOBAL VARIABLES ---
bool isDay = true;
float cloudX = 0.0f;
float sunY = 0.75f;

// Variables from other files
extern bool isRaining;
extern bool isThundering;

// --- CONSTRUCTOR ---
Background::Background() {
    // 1. Create 100 Random Stars
    for (int i = 0; i < 100; i++) {
        Star s;
        // Generate random X between -1.0 and 1.0
        s.x = (rand() / (float)RAND_MAX) * 2.0f - 1.0f;
        // Generate random Y between 0.2 (horizon) and 1.0 (top)
        s.y = 0.2f + (rand() / (float)RAND_MAX) * 0.8f;
        // Random brightness/transparency
        s.alpha = 0.5f + (rand() / (float)RAND_MAX) * 0.5f;
        stars.push_back(s);
    }

    // 2. Create Sun Rays
    for (int i = 0; i < 14; i++) {
        SunRay r;
        r.angle = (2.0f * 3.14159f * i) / 14.0f; // Spread rays in a circle
        r.length = 0.5f + (rand() / (float)RAND_MAX) * 0.3f; // Random length
        r.width = 0.08f + (rand() / (float)RAND_MAX) * 0.05f;
        r.speed = 0.0005f; // Rotation speed
        rays.push_back(r);
    }
}

// --- HELPER FUNCTIONS ---

// Helper: Draws a solid circle
void drawBgCircle(float cx, float cy, float r, int segments, float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * 3.14159f * i / segments; // Calculate angle
        float x = cx + r * cosf(theta); // Polar to Cartesian X
        float y = cy + r * sinf(theta); // Polar to Cartesian Y
        glVertex2f(x, y);
    }
    glEnd();
}

// Helper: Draws a simple wooden chair
void drawChair(float x, float y) {
    glColor3f(0.4f, 0.2f, 0.0f); // Wood color
    glLineWidth(2.0f);

    // Legs and Back support
    glBegin(GL_LINES);
    glVertex2f(x, y);          glVertex2f(x, y + 0.1f);
    glVertex2f(x + 0.05f, y);  glVertex2f(x + 0.05f, y + 0.05f);
    glEnd();

    // Seat
    glBegin(GL_POLYGON);
    glVertex2f(x, y + 0.05f);
    glVertex2f(x + 0.06f, y + 0.05f);
    glVertex2f(x + 0.06f, y + 0.06f);
    glVertex2f(x, y + 0.06f);
    glEnd();

    // Backrest
    glBegin(GL_POLYGON);
    glVertex2f(x, y + 0.05f);
    glVertex2f(x + 0.01f, y + 0.05f);
    glVertex2f(x + 0.01f, y + 0.12f);
    glVertex2f(x, y + 0.12f);
    glEnd();
}

// Helper: Draws a transparent halo (for the sun)
void drawHalo(float cx, float cy, float r, int segments, float alpha) {
    glColor4f(1.0f, 0.9f, 0.4f, alpha); // Yellow with transparency
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * 3.14159f * i / segments;
        glVertex2f(cx + r * cosf(theta), cy + r * sinf(theta));
    }
    glEnd();
}

// --- MAIN DRAW FUNCTION ---
void Background::draw() {
    // 1. Set Sky Color and Brightness
    float bright = 1.0f;
    if (isDay) {
        bright = isRaining ? 0.7f : 1.0f; // Darker if raining during day
    } else {
        bright = isRaining ? 0.3f : 0.5f; // Very dark if raining at night
    }

    float sR, sG, sB; // Sky RGB variables

    if (isThundering) {
        // Flash white for lightning
        sR = 0.9f; sG = 0.9f; sB = 1.0f;
    } else if (isDay) {
        // Day colors (Grey if rain, Blue if sunny)
        sR = isRaining ? 0.4f : 0.53f;
        sG = isRaining ? 0.4f : 0.81f;
        sB = isRaining ? 0.5f : 0.98f;
    } else {
        // Night colors (Dark Blue/Black)
        sR = isRaining ? 0.02f : 0.05f;
        sG = isRaining ? 0.02f : 0.05f;
        sB = isRaining ? 0.05f : 0.2f;
    }

    // Draw the Sky Background
    glColor3f(sR, sG, sB);
    glBegin(GL_POLYGON);
    glVertex2f(-1, 1);
    glVertex2f(1, 1);
    glVertex2f(1, -0.2);
    glVertex2f(-1, -0.2);
    glEnd();

    // 2. Draw Stars (Only at night and no rain)
    if (!isDay && !isRaining) {
        glPointSize(2.0f);
        glBegin(GL_POINTS);
        for (const auto& s : stars) {
            // Twinkle effect: modify alpha slightly
            float twinkle = s.alpha * (0.8f + (rand() / (float)RAND_MAX) * 0.2f);
            glColor4f(1, 1, 1, twinkle);
            glVertex2f(s.x, s.y);
        }
        glEnd();
    }

    // 3. Cloud Logic
    if (isDay || isRaining) {
        
        // A. Normal "Puff" Clouds (Sunny Day)
        if (!isRaining) {
            float cR = 1.0f, cG = 1.0f, cB = 1.0f; // White
            
            // Large cloud body
            drawBgCircle(cloudX, 0.75f, 0.1f, 30, cR, cG, cB);
            drawBgCircle(cloudX - 0.12f, 0.72f, 0.08f, 30, cR, cG, cB);
            drawBgCircle(cloudX + 0.1f, 0.74f, 0.09f, 30, cR, cG, cB);

            // Small trailing cloud
            float offset = 0.6f;
            drawBgCircle(cloudX + offset, 0.65f, 0.09f, 30, cR, cG, cB);
            drawBgCircle(cloudX + offset - 0.09f, 0.63f, 0.07f, 30, cR, cG, cB);
        }

        // B. Realistic Storm Clouds (Nimbostratus / Cumulonimbus)
        if (isRaining) {
            float cR, cG, cB;
            // Lighter grey if lightning, Dark grey otherwise
            if (isThundering) { cR = 0.55f; cG = 0.55f; cB = 0.6f; }
            else { cR = 0.25f; cG = 0.25f; cB = 0.30f; }

            // Loop 3 times to create an "infinite scrolling" effect
            // We draw the same cloud cluster to the left, center, and right
            for (int k = -1; k <= 1; k++) {
                float shift = cloudX + (k * 2.0f); // Position offset

                // Layer 1: The Heavy Base (Flat bottom, typical of storm clouds)
                drawBgCircle(shift - 0.6f, 0.70f, 0.25f, 40, cR, cG, cB);
                drawBgCircle(shift - 0.2f, 0.72f, 0.28f, 40, cR, cG, cB);
                drawBgCircle(shift + 0.2f, 0.70f, 0.28f, 40, cR, cG, cB);
                drawBgCircle(shift + 0.6f, 0.72f, 0.25f, 40, cR, cG, cB);

                // Layer 2: The Mid Body (Connecting mass)
                drawBgCircle(shift - 0.4f, 0.85f, 0.30f, 40, cR, cG, cB);
                drawBgCircle(shift + 0.4f, 0.85f, 0.30f, 40, cR, cG, cB);

                // Layer 3: The Towering Peak (Cumulonimbus top)
                drawBgCircle(shift + 0.0f, 0.90f, 0.35f, 40, cR, cG, cB);
            }
        }
    }

    // 4. Sun & Moon (Hidden during rain)
    if (!isRaining) {
        if (isDay) {
            // Draw Sun
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            
            // Sun Glow/Halos
            drawHalo(0.0f, sunY, 0.25f, 50, 0.2f);
            drawHalo(0.0f, sunY, 0.15f, 50, 0.4f);
            
            // Sun Core
            drawBgCircle(0.0f, sunY, 0.1f, 50, 1.0f, 0.9f, 0.0f);

            // Sun Rays
            glBegin(GL_TRIANGLES);
            for (const auto& r : rays) {
                // Fade ray from center to tip
                glColor4f(1.0f, 1.0f, 0.8f, 0.3f);
                glVertex2f(0.0f, sunY);
                glColor4f(1.0f, 1.0f, 0.8f, 0.0f);
                // Calculate ray tip
                glVertex2f(cosf(r.angle) * r.length, sunY + sinf(r.angle) * r.length);
                glVertex2f(cosf(r.angle + r.width) * r.length, sunY + sinf(r.angle + r.width) * r.length);
            }
            glEnd();
            glDisable(GL_BLEND);

        } else {
            // Draw Moon (Crescent shape logic)
            // 1. Draw full white circle
            drawBgCircle(0.0f, 0.75f, 0.1f, 40, 0.9f, 0.9f, 0.9f);
            // 2. Draw sky-colored circle overlapping slightly to create crescent
            drawBgCircle(0.04f, 0.77f, 0.1f, 40, sR, sG, sB);
        }
    }

    // 5. Draw Ground (Earthy Green)
    glColor3f(0.1f * bright, 0.5f * bright, 0.05f * bright);
    glBegin(GL_POLYGON);
    glVertex2f(-1, -0.1);
    glVertex2f(1, -0.1);
    glVertex2f(1, -1);
    glVertex2f(-1, -1);
    glEnd();

    // 6. Draw Pond & Stone Boundary
    // Stone Boundary
    glColor3f(0.5f * bright, 0.5f * bright, 0.55f * bright);
    glBegin(GL_POLYGON);
    glVertex2f(-0.72f, -0.10f);
    glVertex2f(-0.33f, -0.10f);
    glVertex2f(-0.33f, -0.41f);
    glVertex2f(-0.72f, -0.41f);
    glEnd();
    
    // Water
    glColor3f(0.2f * bright, 0.6f * bright, 0.9f * bright);
    glBegin(GL_POLYGON);
    glVertex2f(-0.70f, -0.12f);
    glVertex2f(-0.35f, -0.12f);
    glVertex2f(-0.35f, -0.39f);
    glVertex2f(-0.70f, -0.39f);
    glEnd();

    // 7. Draw Chairs
    drawChair(-0.80f, -0.25f);
    drawChair(-0.80f, -0.35f);

    // 8. Draw Road
    glColor3f(0.3f * bright, 0.3f * bright, 0.3f * bright); // Dark Grey Road
    glBegin(GL_POLYGON);
    glVertex2f(-1, -0.4);
    glVertex2f(1, -0.4);
    glVertex2f(1, -0.9);
    glVertex2f(-1, -0.9);
    glEnd();

    // Road Stripes
    float stripeColor = isDay ? 1.0f : 0.7f;
    glColor3f(stripeColor, stripeColor, stripeColor);
    glLineWidth(2);
    glBegin(GL_LINES);
    for (float x = -1; x < 1; x += 0.25) {
        glVertex2f(x, -0.65);
        glVertex2f(x + 0.14, -0.65);
    }
    glEnd();
}

// --- UPDATE LOOP ---
void Background::update() {
    // 1. Move Clouds
    // Clouds move faster when raining (0.005) than when sunny (0.003)
    float speed = isRaining ? 0.005f : 0.003f;
    cloudX += speed;
    
    // If clouds move off-screen, reset them to the left side
    if (cloudX > 2.0f) {
        cloudX = -2.0f;
    }

    // 2. Sun Movement (Sunrise animation)
    // Only move sun if it is Day time
    if (!isDay) {
        sunY = 0.5f; // Reset sun position for next day
        return;
    }
    
    // Slowly raise the sun until it hits a certain height
    if (sunY < 0.85) {
        sunY += 0.0005f;
    }

    // Rotate Sun Rays
    for (auto& r : rays) {
        r.angle += r.speed;
    }
}
