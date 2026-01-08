#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h> // Use <GL/glut.h> for Windows
#include <stdlib.h>
#include <math.h>
#include "Scene.hpp"

using namespace std;

// The main Scene object that holds everything (houses, trees, cars, etc.)
Scene *village = nullptr;

// --- CAMERA VARIABLES ---
// 1.732 is the magic number to make the 3D camera look exactly like a 2D canvas
float defaultZoom = 1.732f;
float zoom = defaultZoom;
float centerX = 0.0f;
float centerY = 0.0f;

// This function draws everything to the screen
void display() {
    // Clear the screen and the depth buffer (resetting for new frame)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set up the camera position
    // eye(x,y,z), center(x,y,z), up(x,y,z)
    gluLookAt(centerX, centerY, zoom,
              centerX, centerY, 0.0,
              0.0, 1.0, 0.0);

    // If the village exists, tell it to draw itself
    if (village)
        village->render();

    // Swap buffers to show the new frame (double buffering)
    glutSwapBuffers();
}

// This function handles window resizing
void reshape(int w, int h) {
    glViewport(0, 0, w, h); // Use the whole window
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Set up a perspective view (60 degrees FOV)
    gluPerspective(60.0, 1.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// This function runs every 16ms (~60 frames per second)
void timer(int) {
    if (village)
        village->updateAll(); // Update game logic (move cars, rain, etc.)
    
    glutPostRedisplay(); // Ask GLUT to redraw the screen
    glutTimerFunc(16, timer, 0); // Call this function again in 16ms
}

// Keyboard controls for Game Mechanics
void keyboard(unsigned char key, int, int) {
    switch (key) {
    // --- ZOOM CONTROLS ---
    case 'z': // Zoom In
        zoom -= 0.1f;
        if(zoom < 0.2f) zoom = 0.2f; // Don't zoom in too close
        
        // Safety: If we zoom in, pull the camera back if it's out of bounds
        {
            float visibleRadius = zoom * 0.57735f;
            float maxPan = 1.0f - visibleRadius;
            if (centerX > maxPan) centerX = maxPan;
            if (centerX < -maxPan) centerX = -maxPan;
            if (centerY > maxPan) centerY = maxPan;
            if (centerY < -maxPan) centerY = -maxPan;
        }
        break;

    case 'Z': // Zoom Out (Shift+z)
        zoom += 0.1f;
        // Limit: Cannot zoom out further than default
        if(zoom > defaultZoom){
            zoom = defaultZoom;
            centerX = 0.0f; centerY = 0.0f; // Reset to center
        } else {
            // Adjust pan limits while zooming out
            float visibleRadius = zoom * 0.57735f;
            float maxPan = 1.0f - visibleRadius;
            if (maxPan < 0.0f) maxPan = 0.0f;
            if (centerX > maxPan) centerX = maxPan;
            else if (centerX < -maxPan) centerX = -maxPan;
            if (centerY > maxPan) centerY = maxPan;
            else if (centerY < -maxPan) centerY = -maxPan;
        }
        break;

    case 'o': case 'O': // Reset Camera
        zoom = defaultZoom; centerX = 0.0f; centerY = 0.0f;
        break;

    // --- GAME CONTROLS ---
    case ' ': village->togglePause(); break;   // Pause Animation
    case 'd': case 'D': village->setDay(true); break;  // Set Day
    case 'n': case 'N': village->setDay(false); break; // Set Night
    case 'h': case 'H': village->playHorn(); break;    // Play Horn Sound
    case 'r': case 'R': village->toggleRain(); break;  // Toggle Rain

    case 27: // ESC Key to exit
        system("pkill afplay"); // Stop all sounds
        exit(0);
        break;
    }
    glutPostRedisplay();
}

// Arrow Keys for Panning (Moving Camera Left/Right/Up/Down)
void specialKeys(int key, int x, int y) {
    // Calculate how much we are allowed to pan based on zoom level
    float visibleRadius = zoom * 0.57735f;
    float maxPan = 1.0f - visibleRadius;
    if (maxPan < 0.0f) maxPan = 0.0f;
    
    float moveSpeed = 0.05f;

    switch (key) {
    case GLUT_KEY_LEFT:
        if(centerX - moveSpeed >= -maxPan) centerX -= moveSpeed;
        else centerX = -maxPan;
        break;
    case GLUT_KEY_RIGHT:
        if(centerX + moveSpeed <= maxPan) centerX += moveSpeed;
        else centerX = maxPan;
        break;
    case GLUT_KEY_UP:
        if(centerY + moveSpeed <= maxPan) centerY += moveSpeed;
        else centerY = maxPan;
        break;
    case GLUT_KEY_DOWN:
        if(centerY - moveSpeed >= -maxPan) centerY -= moveSpeed;
        else centerY = -maxPan;
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    // Double Buffer for smooth animation, Depth for 3D layering
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("Village Project - Student Final");

    village = new Scene(); // Create the village

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(16, timer, 0); // Start timer loop

    glutMainLoop(); // Start GLUT main loop
    
    delete village;
    return 0;
}
