#define GL_SILENCE_DEPRECATION

#include "House.hpp"
#include <GLUT/glut.h>

using namespace std;

// PARENT CLASS
House::House(float px, float py) : x(px), y(py) {}


//   HOUSE 1
House1::House1(float px, float py) : House(px, py) {}

void House1::draw()
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f); // Move to position

    // 1. The Foundation (Dark Grey Base)
    glColor3f(0.25f, 0.25f, 0.25f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.3f, 0.0f);
    glVertex2f(0.3f, 0.03f);
    glVertex2f(0.0f, 0.03f);
    glEnd();

    // 2. The Walls (Beige Plaster)
    glColor3f(0.95f, 0.87f, 0.72f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.03f);
    glVertex2f(0.3f, 0.03f);
    glVertex2f(0.3f, 0.35f);
    glVertex2f(0.0f, 0.35f);
    glEnd();

    // 3. The Roof (Red)
    glColor3f(0.50f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.05f, 0.35f);
    glVertex2f(0.35f, 0.35f);
    glVertex2f(0.15f, 0.55f);
    glEnd();

    // 4. The Door
    // Frame
    glColor3f(0.3f, 0.15f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.115f, 0.03f);
    glVertex2f(0.185f, 0.03f);
    glVertex2f(0.185f, 0.185f);
    glVertex2f(0.115f, 0.185f);
    glEnd();
    
    // Door Panel
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.12f, 0.03f);
    glVertex2f(0.18f, 0.03f);
    glVertex2f(0.18f, 0.18f);
    glVertex2f(0.12f, 0.18f);
    glEnd();

    // Knob
    glColor3f(1.0f, 0.8f, 0.0f);
    glPointSize(3.0f);
    glBegin(GL_POINTS);
    glVertex2f(0.17f, 0.10f);
    glEnd();

    // 5. The Windows (Direct X and Y coordinates)
    
    // Left Window
    // Frame (White)
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(0.03f, 0.14f); // Bottom Left
    glVertex2f(0.10f, 0.14f); // Bottom Right
    glVertex2f(0.10f, 0.26f); // Top Right
    glVertex2f(0.03f, 0.26f); // Top Left
    glEnd();
    
    // Glass (Blue)
    glColor3f(0.3f, 0.5f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.04f, 0.15f);
    glVertex2f(0.09f, 0.15f);
    glVertex2f(0.09f, 0.25f);
    glVertex2f(0.04f, 0.25f);
    glEnd();

    // Bars (Black)
    glColor3f(0.2f, 0.2f, 0.2f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(0.065f, 0.15f); glVertex2f(0.065f, 0.25f); // Vertical
    glVertex2f(0.04f, 0.20f);  glVertex2f(0.09f, 0.20f);  // Horizontal
    glEnd();

    // -- Right Window --
    // Frame (White)
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(0.20f, 0.14f);
    glVertex2f(0.27f, 0.14f);
    glVertex2f(0.27f, 0.26f);
    glVertex2f(0.20f, 0.26f);
    glEnd();
    
    // Glass (Blue)
    glColor3f(0.3f, 0.5f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.21f, 0.15f);
    glVertex2f(0.26f, 0.15f);
    glVertex2f(0.26f, 0.25f);
    glVertex2f(0.21f, 0.25f);
    glEnd();
    
    // Bars (Black)
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_LINES);
    glVertex2f(0.235f, 0.15f); glVertex2f(0.235f, 0.25f); // Vertical
    glVertex2f(0.21f, 0.20f);  glVertex2f(0.26f, 0.20f);  // Horizontal
    glEnd();

    glPopMatrix();
}

//   HOUSE 2 (Blue Plaster, Chimney)

House2::House2(float px, float py) : House(px, py) {}

void House2::draw()
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    // 1. The Foundation (Dark Grey - Same as House 1)
    glColor3f(0.25f, 0.25f, 0.25f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.25f, 0.0f);
    glVertex2f(0.25f, 0.03f);
    glVertex2f(0.0f, 0.03f);
    glEnd();

    // 2. The Chimney
    glColor3f(0.5f, 0.2f, 0.1f); // Red Bricks
    glBegin(GL_POLYGON);
    glVertex2f(0.18f, 0.35f);
    glVertex2f(0.23f, 0.35f);
    glVertex2f(0.23f, 0.52f);
    glVertex2f(0.18f, 0.52f);
    glEnd();
    
    glColor3f(0.3f, 0.1f, 0.05f); // Top Cap
    glBegin(GL_POLYGON);
    glVertex2f(0.17f, 0.52f);
    glVertex2f(0.24f, 0.52f);
    glVertex2f(0.24f, 0.54f);
    glVertex2f(0.17f, 0.54f);
    glEnd();

    // 3. The Walls (Solid Plaster - No Lines)
    glColor3f(0.7f, 0.75f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.25f, 0.0f);
    glVertex2f(0.25f, 0.35f);
    glVertex2f(0.0f, 0.35f);
    glEnd();

    // 4. The Roof (Grey)
    glColor3f(0.3f, 0.3f, 0.35f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.03f, 0.35f);
    glVertex2f(0.28f, 0.35f);
    glVertex2f(0.125f, 0.55f);
    glEnd();

    // 5. The Door
    // Frame
    glColor3f(0.35f, 0.2f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(0.07f, 0.0f);
    glVertex2f(0.18f, 0.0f);
    glVertex2f(0.18f, 0.19f);
    glVertex2f(0.07f, 0.19f);
    glEnd();

    // Panel
    glColor3f(0.45f, 0.25f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(0.08f, 0.0f);
    glVertex2f(0.17f, 0.0f);
    glVertex2f(0.17f, 0.18f);
    glVertex2f(0.08f, 0.18f);
    glEnd();

    // Knob
    glColor3f(1.0f, 0.8f, 0.0f);
    glPointSize(3.0f);
    glBegin(GL_POINTS);
    glVertex2f(0.155f, 0.09f);
    glEnd();

    // 6. The Windows (Direct X and Y coordinates)

    // -- Left Window --
    // Frame (White)
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.02f, 0.21f); // Bottom Left
    glVertex2f(0.10f, 0.21f); // Bottom Right
    glVertex2f(0.10f, 0.29f); // Top Right
    glVertex2f(0.02f, 0.29f); // Top Left
    glEnd();
    
    // Glass (Lit Yellow)
    glColor3f(0.9f, 0.9f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(0.03f, 0.22f);
    glVertex2f(0.09f, 0.22f);
    glVertex2f(0.09f, 0.28f);
    glVertex2f(0.03f, 0.28f);
    glEnd();

    // Bars (Dark Grey)
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES);
    glVertex2f(0.06f, 0.22f); glVertex2f(0.06f, 0.28f); // Vertical
    glVertex2f(0.03f, 0.25f); glVertex2f(0.09f, 0.25f); // Horizontal
    glEnd();

    // Right Window 
    // Frame (White)
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.15f, 0.21f); // Bottom Left
    glVertex2f(0.23f, 0.21f); // Bottom Right
    glVertex2f(0.23f, 0.29f); // Top Right
    glVertex2f(0.15f, 0.29f); // Top Left
    glEnd();

    // Glass (Lit Yellow)
    glColor3f(0.9f, 0.9f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(0.16f, 0.22f);
    glVertex2f(0.22f, 0.22f);
    glVertex2f(0.22f, 0.28f);
    glVertex2f(0.16f, 0.28f);
    glEnd();

    // Bars (Dark Grey)
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES);
    glVertex2f(0.19f, 0.22f); glVertex2f(0.19f, 0.28f); // Vertical
    glVertex2f(0.16f, 0.25f); glVertex2f(0.22f, 0.25f); // Horizontal
    glEnd();

    glPopMatrix();
}
