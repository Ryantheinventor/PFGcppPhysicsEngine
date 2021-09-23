#pragma once
#include "baseGame.h"
#include "testObject.h"
class demoGame : public baseGame
{
public:
	void onInit() override;
    void onTick() override;
    void onFixedTick() override;
	void onDraw() const override;
    void onExit() override;

    float curWait = 0;
    //// Called internally when game-specifc initialization occurs
    //void virtual onInit() { }

    //// Called internally when game-specifc tick occurs
    //void virtual onTick() { }

    //// Called internally when game-specific fixed tickrate logic occurs
    //void virtual onFixedTick() { }

    //// Called internally when game-specifc drawing occurs
    //void virtual onDraw() const { }

    //// Called internally when game-specifc clean-up occurs
    //void virtual onExit() { }
};

