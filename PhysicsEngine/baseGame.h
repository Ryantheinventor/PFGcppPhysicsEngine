#pragma once
#include "raylib/raylib.h"
#include <iostream>
#include <vector>
#include "gameObject.h"
class baseGame
{
protected:
    float accumulatedFixedTime;
    std::vector<gameObject> gameObjects;
    // Called internally when game-specifc initialization occurs
    void virtual onInit() { }

    // Called internally when game-specifc tick occurs
    void virtual onTick() { }

    // Called internally when game-specific fixed tickrate logic occurs
    void virtual onFixedTick() { }

    // Called internally when game-specifc drawing occurs
    void virtual onDraw() const { }

    // Called internally when game-specifc clean-up occurs
    void virtual onExit() { }

public:
    float targetFixedStep = 0.016f;
    float maxAccumulatedTime = 0.16f;//max of 10 physics tick per main loop
    // Trivial constructor
    baseGame();

    // Initializes the game window
    void init();

    // Poll for input, update timers, etc.
    void tick();

    // Tick objects working on a fixed tick rate
    void tickFixed();

    // Draw the current world state
    void draw() const;

    // Close the game and shutdown
    void exit();

    // Returns true if the game is trying to shut down
    bool shouldClose() const;

    // Returns true when enough time has passed for a fixed tick to occur
    bool shouldTickFixed() const;

    static glm::vec2 worldToScreen(glm::vec2 worldPos);
    static glm::vec2 screenToWorld(glm::vec2 worldPos);
    static void destroy(gameObject go);
};