#define GL_SILENCE_DEPRECATION

#include "Bus.hpp"
#include <math.h>
#include <GLUT/glut.h>
extern bool isMoving; extern bool greenLight; extern bool isDay;
Bus::Bus(float startX, float startY, float dir) : x(startX), y(startY), direction(dir) { speed = 0.005f; }
void Bus::draw() {
    bool lights = !isDay;
    glColor3f(1.0f, 0.8f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x+0.5, y);
    glVertex2f(x+0.5, y+0.18);
    glVertex2f(x, y+0.18); glEnd();
    glColor3f(0.3, 0.7, 1.0);
    for(int i=0; i<5; i++)
    {
        float wx = x+0.02+(i*0.09);
        glBegin(GL_POLYGON);
        glVertex2f(wx, y+0.08);
        glVertex2f(wx+0.08, y+0.08);
        glVertex2f(wx+0.08, y+0.15);
        glVertex2f(wx, y+0.15);
        glEnd();
    }
    
    glColor3f(0.1,0.1,0.1);
    glBegin(GL_POLYGON);
    for(int i=0;i<20;i++) glVertex2f((x+0.08)+0.04*cos(i*6.28/20), y+0.04*sin(i*6.28/20));
    glEnd();
    
    glBegin(GL_POLYGON);
    for(int i=0;i<20;i++) glVertex2f((x+0.38)+0.04*cos(i*6.28/20), y+0.04*sin(i*6.28/20));
    glEnd();
    
    if(direction > 0) {
        if(lights)
        {
            glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA); glColor4f(1,1,0.9,0.4); glBegin(GL_TRIANGLES); glVertex2f(x+0.5,y+0.05); glVertex2f(x+0.9,y+0.1); glVertex2f(x+0.9,y-0.1);
                glEnd();
            
            glDisable(GL_BLEND);
            glColor3f(1,1,0.7);
        }
        
        else
        glColor3f(0.8,0.8,0);
        glBegin(GL_POLYGON);
        glVertex2f(x+0.49,y+0.04); glVertex2f(x+0.505,y+0.04); glVertex2f(x+0.505,y+0.07); glVertex2f(x+0.49,y+0.07);
        glEnd();
    }
    else
    {
        if(lights) { glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA); glColor4f(1,1,0.9,0.4); glBegin(GL_TRIANGLES);
            glVertex2f(x,y+0.05); glVertex2f(x-0.4,y+0.1); glVertex2f(x-0.4,y-0.1);
            glEnd();
            
            glDisable(GL_BLEND);
            glColor3f(1,1,0.7); } else glColor3f(0.8,0.8,0);
            glBegin(GL_POLYGON);
            glVertex2f(x-0.005,y+0.04);
        
            glVertex2f(x+0.01,y+0.04);
            glVertex2f(x+0.01,y+0.07);
            glVertex2f(x-0.005,y+0.07)
        ;
        glEnd();
    }
}
void Bus::update()
{
    if (!isMoving || !greenLight) return; x += direction * speed;
    if (x > 1.4f) x = -1.4f;
    if (x < -1.4f) x = 1.4f;
}
