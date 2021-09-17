#pragma once
#include "raylib/raylib.h"
#include <iostream>
#include <vector>
#include "gameObject.h"
#include "collision.h" 
#include <unordered_map>
#include "enumOr.h"
// a type alias to make things more readable
using collisionPair = uint8_t;
// the function signature for any collision detection test
using collisionFunc = bool(*)(const glm::vec2&, const shape&, const glm::vec2&, const shape&);
// a map that takes a collision pair and returns the correct function to call
using collisionMap = std::unordered_map<collisionPair, collisionFunc>;
class baseGame
{
protected:
    float accumulatedFixedTime;
    
   
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
    static std::vector<gameObject> gameObjects;
    float targetFixedStep;
    float maxAccumulatedTime;//max of 10 physics tick per main loop
    static float screenSizeMultiplier;
    collisionMap map;
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


};