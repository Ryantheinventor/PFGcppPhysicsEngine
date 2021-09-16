#include "baseGame.h"


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
	accumulatedFixedTime += GetFrameTime();
	if (accumulatedFixedTime > maxAccumulatedTime)
	{
		accumulatedFixedTime = maxAccumulatedTime;
	}
	//aa
	for (int i = 0; i < gameObjects.size(); i++) 
	{
		gameObjects[i].interpolate(0.5f);
	}

	onTick();
}

void baseGame::tickFixed()
{
	accumulatedFixedTime -= targetFixedStep;
	for (int i = 0; i < gameObjects.size(); i++) 
	{
		gameObjects[i].tickPhys(targetFixedStep);
	}
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

glm::vec2 baseGame::worldToScreen(glm::vec2 worldPos)
{
	return worldPos * 10.f;
}

glm::vec2 baseGame::screenToWorld(glm::vec2 screenPos)
{
	return screenPos * 0.1f;
}
