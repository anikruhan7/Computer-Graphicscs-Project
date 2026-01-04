// Tree.h
#ifndef TREE_H
#define TREE_H

#include "GameObject.h"

class Tree : public GameObject
{
protected:
    float x, y, scale;

public:
    Tree(float px, float py, float s);
};

class NormalTree : public Tree
{
public:
    NormalTree(float px, float py, float s);
    void draw() override;
};

class SlimTree : public Tree
{
public:
    SlimTree(float px, float py, float s);
    void draw() override;
};

#endif