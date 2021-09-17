#include "demoGame.h"

void demoGame::onInit() {}

void demoGame::onTick()
{
	if (IsMouseButtonPressed(0)) 
	{
		glm::vec2 mousePos(GetMousePosition().x, GetMousePosition().y);
		glm::vec2 worldMPos = screenToWorld(mousePos);
		gameObject newObject = gameObject();
		newObject.setPos(worldMPos);
		newObject.collider.type = shapeType::CIRCLE;
		newObject.collider.circleData.radius = 0.5f;
		gameObjects.push_back(newObject);
	}
}

void demoGame::onFixedTick() {}

void demoGame::onDraw() const
{
	ClearBackground(RAYWHITE);
	//DrawText("Hello Physics", 320, 200, 20, RED);
	//draw game objects
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i].OnDraw();
	}
}

void demoGame::onExit() {}