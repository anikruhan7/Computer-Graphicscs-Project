#ifndef SCENE_H
#define SCENE_H
#include "GameObject.h"
#include <vector>

class Scene {
private:
    std::vector<GameObject *> objects; // List of all objects in the game

public:
    Scene();
    ~Scene();
    void render();
    void updateAll();
    
    // Controls
    void togglePause();
    void setDay(bool status);
    void playHorn();
    void toggleRain();
};
#endif
