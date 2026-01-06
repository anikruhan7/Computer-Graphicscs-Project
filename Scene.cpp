#include "Scene.h"
#include "Background.h"
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
    cout << "--- SPAWNING 2 BUSES + 4 CARS (TOTAL) ---" << endl;

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

Scene::~Scene()
{
    for (auto obj : objects)
        delete obj;
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