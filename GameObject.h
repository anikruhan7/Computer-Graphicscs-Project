#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GLUT/glut.h>

class GameObject
{
public:
    virtual void draw() = 0;
    virtual void update() {}
    virtual ~GameObject() {}
};

#endif