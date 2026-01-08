#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <GLUT/glut.h>

// Abstract class: Forces all children to have a draw() function
class GameObject {
public:
    virtual void draw() = 0;   // Pure virtual function
    virtual void update() {}   // Optional update function
    virtual ~GameObject() {}   // Virtual destructor
};
#endif
