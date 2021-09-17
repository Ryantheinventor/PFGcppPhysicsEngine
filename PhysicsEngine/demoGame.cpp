#include "demoGame.h"

void demoGame::onInit() {}

void demoGame::onTick()
{
	if (IsMouseButtonDown(0))
	{
		glm::vec2 mousePos(GetMousePosition().x, GetMousePosition().y);
		glm::vec2 worldMPos = screenToWorld(mousePos);
		gameObject* newObject = new gameObject();
		(*newObject).setPos(worldMPos);
		(*newObject).collider.type = shapeType::AABB;
		(*newObject).collider.aabbData.height = 1.f;
		(*newObject).collider.aabbData.width = 1.f;
		gameObjects.push_back(newObject);
	}

	if (IsMouseButtonDown(1))
	{
		glm::vec2 mousePos(GetMousePosition().x, GetMousePosition().y);
		glm::vec2 worldMPos = screenToWorld(mousePos);
		gameObject* newObject = new gameObject();
		(*newObject).setPos(worldMPos);
		(*newObject).collider.type = shapeType::CIRCLE;
		(*newObject).collider.circleData.radius = 0.5f;
		gameObjects.push_back(newObject);
	}
}

void demoGame::onFixedTick() {}

void demoGame::onDraw() const
{
	ClearBackground(RAYWHITE);
	//DrawText("Hello Physics", 320, 200, 20, RED);
	//draw game objects
	for (int i = 0; i < baseGame::gameObjects.size(); i++)
	{
		(*baseGame::gameObjects[i]).OnDraw();
	}
}

void demoGame::onExit() {}