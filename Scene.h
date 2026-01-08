#ifndef SCENE_H
#define SCENE_H

#include "GameObject.h"
#include <vector>

class Scene
{
public:
    enum Mode { VILLAGE, CITY };

private:
    std::vector<GameObject *> objects;
    Mode currentMode = VILLAGE;

    // Helpers to build scene variants
    void clearObjects();
    void createVillage();
    void createCity();

public:
    Scene();
    ~Scene();
    void render();
    void updateAll();
    void togglePause();
    void setDay(bool status);
    void playHorn();

    // Mode control
    void setMode(Mode m);
    void toggleMode();
    Mode getMode() const { return currentMode; }
};

#endif