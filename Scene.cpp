#include "Scene.h"
#include "Background.h"
#include "CityBackground.h"
#include "Building.h"
#include "Plane.h"
#include "Ship.h"
#include "Tree.h"
#include "House.h"
#include "Car.h"
#include "TrafficLight.h"
#include "Bus.h"
#include "Bird.h"
#include <iostream>

using namespace std;

// Global variables
bool isMoving = true;
bool greenLight = true;
int trafficTimer = 0;
bool daySoundPlaying = false;
bool nightSoundPlaying = false;

Scene::Scene()
{
    // Start with the village as default
    createVillage();
}


void Scene::clearObjects()
{
    for (auto obj : objects)
        delete obj;
    objects.clear();
}

void Scene::createVillage()
{
    cout << "--- CREATING VILLAGE SCENE ---" << endl;
    clearObjects();

    objects.push_back(new Background());

    // Birds
    objects.push_back(new Bird(-1.0f, 0.8f, 0.005f));
    objects.push_back(new Bird(0.5f, 0.78f, 0.006f));
    objects.push_back(new Bird(-1.8f, 0.86f, 0.008f));
    objects.push_back(new Bird(0.2f, 0.88f, 0.005f));

    // Scenery
    objects.push_back(new NormalTree(-0.92f, -0.1f, 0.4f));
    objects.push_back(new NormalTree(-0.85f, -0.1f, 0.3f));
    // Added more small trees on the left side
    objects.push_back(new SlimTree(-0.95f, -0.1f, 0.8f));
    objects.push_back(new NormalTree(-0.80f, -0.1f, 0.2f));
    objects.push_back(new SlimTree(-0.3f, -0.22f, 1.0f));
    // Added medium and large trees near the houses and to the right
    objects.push_back(new NormalTree(-0.2f, -0.22f, 0.6f));
    objects.push_back(new NormalTree(0.35f, -0.22f, 1.2f));
    objects.push_back(new SlimTree(0.7f, -0.2f, 1.1f));
    objects.push_back(new NormalTree(0.9f, -0.15f, 0.9f));
    objects.push_back(new HouseType1(0.0f, -0.25f));
    objects.push_back(new HouseType2(0.55f, -0.25f));
    objects.push_back(new TrafficLight());

    // TRAFFIC

    // TOP LANE - Moving Right
    // 1 Bus + 2 Cars
    objects.push_back(new Bus(0.6f, -0.55f, 1.0f));                    // Bus
    objects.push_back(new Car(0.0f, -0.55f, 1.0f, 0.0f, 0.0f, 1.0f));  // Red Car
    objects.push_back(new Car(-0.5f, -0.55f, 0.0f, 1.0f, 0.0f, 1.0f)); // Green Car

    // BOTTOM LANE-Moving Left
    // 1 Bus + 2 Cars
    objects.push_back(new Bus(-0.6f, -0.80f, -1.0f));                  //  Bus
    objects.push_back(new Car(0.0f, -0.80f, 0.0f, 1.0f, 1.0f, -1.0f)); //  Cyan Car
    objects.push_back(new Car(0.5f, -0.80f, 1.0f, 0.5f, 0.0f, -1.0f)); // Orange Car
}

void Scene::createCity()
{
    cout << "--- CREATING CITY SCENE ---" << endl;
    clearObjects();

    // City background contains river + road layout
    objects.push_back(new CityBackground());

    // Buildings / Skyscrapers (sit on the ground top, a little bit lowered)
    float startX = -0.95f;
    for (int i = 0; i < 10; ++i)
    {
        float w = 0.16f;
        float h = 0.35f + (i % 4) * 0.14f + (i / 7) * 0.18f; // variety in height
        float cx = startX + i * 0.19f;
        float cy = -0.20f; // base y sits on ground top
        float r = 0.2f + 0.06f * (i % 3);
        float g = 0.2f + 0.05f * ((i + 1) % 3);
        float b = 0.25f + 0.04f * ((i + 2) % 3);
        objects.push_back(new Building(cx, cy, w, h, r, g, b));
    }

    // Small trees along the ground for visual separation (add more for density)
    objects.push_back(new SlimTree(-0.92f, -0.20f, 0.8f));
    objects.push_back(new NormalTree(-0.7f, -0.22f, 0.5f));
    objects.push_back(new NormalTree(-0.45f, -0.20f, 0.6f));
    objects.push_back(new SlimTree(-0.2f, -0.22f, 0.75f));
    objects.push_back(new NormalTree(0.05f, -0.20f, 0.6f));
    objects.push_back(new NormalTree(0.3f, -0.22f, 0.7f));
    objects.push_back(new SlimTree(0.6f, -0.20f, 0.6f));
    objects.push_back(new SlimTree(0.85f, -0.22f, 0.7f));

    // Add plane in sky and ship on river
    objects.push_back(new Plane(-1.2f, 0.92f, 0.010f));
    // Ships should be placed on the lower river we drew (-0.56 to -0.72)
    objects.push_back(new Ship(-1.1f, -0.64f, 0.0015f, 1.3f));
    objects.push_back(new Ship(-0.4f, -0.68f, 0.0022f, 0.95f));

    // Road lanes (on the bottom road strip -0.84..-1.00): reduced density and repositioned
    float topLaneY = -0.86f;
    float bottomLaneY = -0.94f;

    for (int i = 0; i < 4; ++i)
        objects.push_back(new Car(-1.1f + i * 0.6f, topLaneY, (i % 3 == 0 ? 1.0f : 0.0f), (i % 3 == 1 ? 1.0f : 0.5f), (i % 3 == 2 ? 1.0f : 0.0f), 1.0f));

    for (int i = 0; i < 4; ++i)
        objects.push_back(new Car(1.1f - i * 0.6f, bottomLaneY, (i % 2 == 0 ? 0.2f : 0.9f), (i % 2 == 0 ? 0.6f : 0.2f), (i % 2 == 0 ? 1.0f : 0.1f), -1.0f));

    // Single city bus on bottom lane (moved inward a bit)
    objects.push_back(new Bus(0.4f, bottomLaneY, -1.0f));
}


Scene::~Scene()
{
    clearObjects();
}

void Scene::setMode(Mode m)
{
    if (m == currentMode)
        return;
    currentMode = m;
    if (currentMode == VILLAGE)
        createVillage();
    else
        createCity();
}

void Scene::toggleMode()
{
    if (currentMode == VILLAGE)
        setMode(CITY);
    else
        setMode(VILLAGE);
}
void Scene::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    for (auto obj : objects)
        obj->draw();
    glFlush();
}

void Scene::updateAll()
{
    if (isMoving)
    {
        trafficTimer++;
        if (trafficTimer > 300)
        {
            greenLight = !greenLight;
            trafficTimer = 0;
        }
        for (auto obj : objects)
            obj->update();
    }

    // Sound Logic
    if (isDay && !daySoundPlaying)
    {
        system("pkill afplay");
        system("afplay birds.wav &");
        daySoundPlaying = true;
        nightSoundPlaying = false;
    }
    else if (!isDay && !nightSoundPlaying)
    {
        system("pkill afplay");
        system("afplay crickets.wav &");
        nightSoundPlaying = true;
        daySoundPlaying = false;
    }
    glutPostRedisplay();
}

void Scene::togglePause() { isMoving = !isMoving; }
void Scene::setDay(bool status) { isDay = status; }
void Scene::playHorn() { system("afplay horn.wav &"); }