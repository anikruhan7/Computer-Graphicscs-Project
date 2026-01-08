#define GL_SILENCE_DEPRECATION

#include "Scene.hpp"
#include "Background.hpp"
#include "Tree.hpp"
#include "House.hpp"
#include "Car.hpp"
#include "TrafficLight.hpp"
#include "Bus.hpp"
#include "Bird.hpp"
#include "Rain.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

// --- GLOBAL VARIABLES (Shared across files) ---
bool isMoving = true;
bool greenLight = true;
bool isRaining = false;
bool isThundering = false;

// Audio Status Flags
bool daySoundPlaying = false;
bool nightSoundPlaying = false;
bool rainSoundPlaying = false;

// Timers for logic
int trafficTimer = 0;
int thunderTimer = 0;

Scene::Scene() {
    cout << "--- VILLAGE LOADED ---" << endl;
    
    // 1. Add Background and Rain first (so they are behind everything)
    objects.push_back(new Background());
    objects.push_back(new Rain());

    // 2. Add Realistic Trees
    // Placed at specific coordinates to look nice
    objects.push_back(new SlimTree(-0.92f, -0.15f, 0.6f)); // Small left tree
    objects.push_back(new SlimTree(-0.85f, -0.15f, 0.9f));
    objects.push_back(new NormalTree(-0.25f, -0.15f, 0.8f));
    objects.push_back(new NormalTree(0.40f, -0.15f, 1.0f));
    objects.push_back(new SlimTree(0.75f, -0.15f, 0.85f));

    // 3. Add Houses
    objects.push_back(new House1(0.0f, -0.25f));
    objects.push_back(new House2(0.55f, -0.25f)); // Realistic house on right

    // 4. Add Traffic Light
    objects.push_back(new TrafficLight());

    // 5. Add Vehicles
    objects.push_back(new Bus(0.6f, -0.55f, 1.0f));
    objects.push_back(new Car(0.0f, -0.55f, 1.0f, 0.0f, 0.0f, 1.0f));
    objects.push_back(new Bus(-0.6f, -0.80f, -1.0f));
    objects.push_back(new Car(0.0f, -0.80f, 0.0f, 1.0f, 1.0f, -1.0f));

    // 6. Add Flock of Birds (Random positions)
    for(int i=0; i<6; i++) {
        float bx = (rand() % 200) / 100.0f - 1.0f; // Random X
        float by = 0.5f + (rand() % 40) / 100.0f;  // Random Y
        float bs = 0.003f + (rand() % 5) / 1000.0f; // Random Speed
        objects.push_back(new Bird(bx, by, bs));
    }
}

Scene::~Scene() {
    // Delete all objects to free memory
    for (auto obj : objects) delete obj;
    system("pkill afplay"); // Stop sound on exit
}

void Scene::render() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear screen
    for (auto obj : objects) obj->draw(); // Draw every object
    glFlush();
}

void Scene::updateAll() {
    // 1. Traffic Logic
    if (isMoving) {
        trafficTimer++;
        if (trafficTimer > 300) { // Change light every 300 frames
            greenLight = !greenLight;
            trafficTimer = 0;
        }
        for (auto obj : objects) obj->update();
    }

    // 2. Thunderstorm Logic (Only during rain)
    if (isRaining) {
        thunderTimer++;
        // Wait 15 seconds (900 frames) then storm for 5 seconds
        if (thunderTimer >= 900 && thunderTimer < 1200) {
            if (thunderTimer == 900) system("afplay thunder.wav -t 5 &");
            // Randomly flicker the lightning flag
            isThundering = (rand() % 10 > 6);
        } else {
            isThundering = false;
        }
        if (thunderTimer >= 1200) thunderTimer = 0; // Reset loop
    } else {
        isThundering = false;
        thunderTimer = 0;
    }

    // 3. Audio System (Strict Logic)
    if (isRaining) {
        // If it starts raining, stop nature sounds and play rain/wind
        if (!rainSoundPlaying) {
            system("pkill afplay");
            system("afplay rain.wav &");
            system("afplay wind.wav &");
            rainSoundPlaying = true;
            daySoundPlaying = false;
            nightSoundPlaying = false;
        }
    } else {
        // If rain stops, kill rain sound
        if (rainSoundPlaying) {
            system("pkill afplay");
            rainSoundPlaying = false;
            daySoundPlaying = false;
            nightSoundPlaying = false;
        }
        
        // Handle Day/Night sounds
        extern bool isDay; // access global variable
        if (isDay) {
            if (!daySoundPlaying) {
                system("pkill afplay"); // Kill night sounds
                system("afplay birds.wav &");
                daySoundPlaying = true;
                nightSoundPlaying = false;
            }
        } else {
            if (!nightSoundPlaying) {
                system("pkill afplay"); // Kill day sounds
                system("afplay crickets.wav &");
                nightSoundPlaying = true;
                daySoundPlaying = false;
            }
        }
    }
    glutPostRedisplay();
}

void Scene::togglePause() { isMoving = !isMoving; }
void Scene::setDay(bool status) { extern bool isDay; isDay = status; }
void Scene::playHorn() { system("afplay horn.wav &"); }
void Scene::toggleRain() { isRaining = !isRaining; }
