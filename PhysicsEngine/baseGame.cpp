#include "baseGame.h"
#include <iostream>

baseGame::baseGame() 
{

}

void baseGame::init()
{
	InitWindow(800, 450, "Hello Physics");

	SetTargetFPS(144);
	onInit();
}

void baseGame::tick()
{
	std::cout << "game tick" << GetFrameTime() << "\n";
	accumulatedFixedTime += GetFrameTime();
	if (accumulatedFixedTime > maxAccumulatedTime)
	{
		accumulatedFixedTime = maxAccumulatedTime;
	}
	onTick();
}

void baseGame::tickFixed()
{
	std::cout << "physics tick\n";
	accumulatedFixedTime -= targetFixedStep;
	onFixedTick();
}

void baseGame::draw() const
{
	BeginDrawing();

	onDraw();

	EndDrawing();

}

void baseGame::exit()
{
	onExit();
	CloseWindow();
}

bool baseGame::shouldClose() const
{
	return WindowShouldClose();
}

bool baseGame::shouldTickFixed() const
{
	return accumulatedFixedTime >= targetFixedStep;
}