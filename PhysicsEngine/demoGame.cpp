#include "demoGame.h"

void demoGame::onInit()
{
	gameObjects.push_back(gameObject());
	gameObjects[0].addVelocity(glm::vec2(10.f,0.f));
}

void demoGame::onTick()
{
	if (IsMouseButtonPressed(0)) 
	{
		glm::vec2 mousePos(GetMousePosition().x, GetMousePosition().y);
		glm::vec2 worldMPos = screenToWorld(mousePos);
		gameObject newObject = gameObject();
		newObject.setPos(worldMPos);
		gameObjects.push_back(newObject);
	}
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i].Tick();
	}
}
void demoGame::onFixedTick() 
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i].FixedTick();
	}
}

void demoGame::onDraw() const
{
	ClearBackground(RAYWHITE);
	DrawText("Hello Physics", 320, 200, 20, RED);
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i].OnDraw();
	}
}

void demoGame::onExit() 
{
	
}