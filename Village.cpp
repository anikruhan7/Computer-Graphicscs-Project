// Assalamualaikum, Sir
// ANIK RUHAN
// ID = 23-50245-1
// Section = L

#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <math.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Sky //
    glColor3f(0.53f, 0.81f, 0.98f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(1.0f, -0.2f);
    glVertex2f(-1.0f, -0.2f);
    glEnd();

    // Ground //
    glColor3f(0.0, 0.55, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, -0.2f);
    glVertex2f(1.0f, -0.2f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();

    // Road //
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, -0.45f);
    glVertex2f(1.0f, -0.45f);
    glVertex2f(1.0f, -0.8f);
    glVertex2f(-1.0f, -0.8f);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    for (float x = -1.0f; x < 1.0f; x += 0.25f)
    {
        glVertex2f(x, -0.642f);
        glVertex2f(x + 0.14f, -0.642f);
    }
    glEnd();

    // Sun //
    glColor3f(1.0f, 0.84f, 0.0f);
    float r = 0.1f;
    int segments = 100;
    glBegin(GL_POLYGON);
    for (int i = 0; i <= segments; i++)
    {
        float angle = 2 * M_PI * i / segments;
        float x = r * cos(angle);
        float y = r * sin(angle);
        glVertex2f(x + 0.0f, y + 0.8f);
    }
    glEnd();

    // Left
    glColor3f(0.5f, 0.2f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.85f, -0.25f);
    glVertex2f(-0.80f, -0.25f);
    glVertex2f(-0.80f, 0.12f);
    glVertex2f(-0.85f, 0.12f);
    glEnd();
    glColor3f(0.0f, 0.5f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.90f, 0.12f);
    glVertex2f(-0.75f, 0.12f);
    glVertex2f(-0.825f, 0.32f);
    glEnd();

    // Middle
    glColor3f(0.5f, 0.2f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.55f, -0.25f);
    glVertex2f(-0.50f, -0.25f);
    glVertex2f(-0.50f, 0.12f);
    glVertex2f(-0.55f, 0.12f);
    glEnd();
    glColor3f(0.0f, 0.5f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.60f, 0.12f);
    glVertex2f(-0.45f, 0.12f);
    glVertex2f(-0.525f, 0.28);
    glEnd();

    // Right
    glColor3f(0.5f, 0.2f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(0.00f, -0.25f);
    glVertex2f(0.05f, -0.25f);
    glVertex2f(0.05f, 0.12f);
    glVertex2f(0.00f, 0.12f);
    glEnd();
    glColor3f(0.0f, 0.5f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.03f, 0.12f);
    glVertex2f(0.08f, 0.12f);
    glVertex2f(0.025f, 0.30f);
    glEnd();

    // House//
    glColor3f(0.95f, 0.87f, 0.72f);
    glBegin(GL_POLYGON);
    glVertex2f(0.3f, -0.22f);
    glVertex2f(0.6f, -0.22f);
    glVertex2f(0.6f, 0.1f);
    glVertex2f(0.3f, 0.1f);
    glEnd();

    glColor3f(0.25f, 0.25f, 0.25f);
    glBegin(GL_POLYGON);
    glVertex2f(0.3f, -0.25f);
    glVertex2f(0.6f, -0.25f);
    glVertex2f(0.6f, -0.22f);
    glVertex2f(0.3f, -0.22f);
    glEnd();

    glColor3f(0.50f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.25f, 0.1f);
    glVertex2f(0.65f, 0.1f);
    glVertex2f(0.45f, 0.3f);
    glEnd();

    // Windows//
    glColor3f(0.3f, 0.5f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.340f, -0.090f);
    glVertex2f(0.386f, -0.090f);
    glVertex2f(0.386f, -0.025f);
    glVertex2f(0.340f, -0.025f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.514f, -0.090f);
    glVertex2f(0.56f, -0.090f);
    glVertex2f(0.56f, -0.025f);
    glVertex2f(0.514f, -0.025f);
    glEnd();

    // Door//
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_POLYGON);
    glVertex2f(0.42f, 0.001f);
    glVertex2f(0.48f, 0.001f);
    glVertex2f(0.48f, -0.18f);
    glVertex2f(0.42f, -0.18f);
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("A Village Seen");
    glutDisplayFunc(display);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutMainLoop();
    return 0;
}

// using VS Code MacOS using command : clang++ main.cpp -std=c++17 -framework OpenGL -framework GLUT -DGL_SILENCE_DEPRECATION -o main && ./main
