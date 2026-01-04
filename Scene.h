#ifndef SCENE_H
#define SCENE_H

#include "GameObject.h"
#include <vector>

class Scene
{
private:
    std::vector<GameObject *> objects;

public:
    Scene();
    ~Scene();
    void render();
    void updateAll();
    void togglePause();
    void setDay(bool status); // <--- CHANGED: Logic for D/N keys
    void playHorn();
};

#endif