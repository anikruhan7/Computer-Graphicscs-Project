#define GL_SILENCE_DEPRECATION

#include <GLUT/glut.h>
#include <stdlib.h>
#include "Scene.h"

using namespace std;

Scene *village = nullptr;

// --- ZOOM VARIABLES ---
// 1.732f is the exact math magic number (1.0 / tan(30))
// to make the 3D view match your original -1 to 1 coordinates perfectly.
float defaultZoom = 1.732f;
float zoom = defaultZoom;

// Camera Position
float centerX = 0.0f;
float centerY = 0.0f;

void display()
{
    // Clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // --- CAMERA SETUP ---
    // Eye(x,y,z), Center(x,y,z), Up(0,1,0)
    gluLookAt(centerX, centerY, zoom,
              centerX, centerY, 0.0,
              0.0, 1.0, 0.0);

    if (village)
        village->render();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    // 1. Set Viewport to fill the entire window
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // 2. FORCE ASPECT RATIO TO 1.0
    // We use '1.0' instead of '(float)w/h'.
    // This replicates your original code's behavior of stretching
    // the -1 to 1 coordinates to fill the whole window, preventing gaps on the sides.
    gluPerspective(60.0, 1.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

void timer(int)
{
    if (village)
        village->updateAll();

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void keyboard(unsigned char key, int, int)
{
    switch (key)
    {
    // --- ZOOM CONTROLS ---
    case 'z':
        // Zoom In
        zoom -= 0.1f;
        if (zoom < 0.2f)
            zoom = 0.2f; // Stop before hitting the ground
        break;

    case 'Z':
        // Zoom Out (Shift + z)
        zoom += 0.1f;
        break;

    case 'o':
    case 'O':
        // RESET to Original Position (Fit to Window)
        zoom = defaultZoom;
        centerX = 0.0f;
        centerY = 0.0f;
        break;

    // --- ORIGINAL CONTROLS ---
    case ' ':
        village->togglePause();
        break;
    case 'd':
    case 'D':
        village->setDay(true);
        break;
    case 'n':
    case 'N':
        village->setDay(false);
        break;
    case 'h':
    case 'H':
        village->playHorn();
        break;
    case 27: // ESC key
        system("pkill afplay");
        exit(0);
        break;
    }
    glutPostRedisplay();
}

// Optional: Arrow Keys for Panning (Move Left/Right/Up/Down)
void specialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        centerX -= 0.05f;
        break;
    case GLUT_KEY_RIGHT:
        centerX += 0.05f;
        break;
    case GLUT_KEY_UP:
        centerY += 0.05f;
        break;
    case GLUT_KEY_DOWN:
        centerY -= 0.05f;
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    // Added GLUT_DEPTH for 3D camera handling
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("Village - Zoom (z/Z) & Reset (O)");

    village = new Scene();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(16, timer, 0);

    glutMainLoop();
    delete village;
    return 0;
}