#include "demoGame.h"

void demoGame::onInit() {}

void demoGame::onTick()
{
	float newY = GetRandomValue(-50, 140) / 10.f;
	float newX = GetRandomValue(1, 250) / 10.f;
	if (curWait > 0.07f  && IsKeyDown(KEY_SPACE)) 
	{
		glm::vec2 worldMPos = glm::vec2(newX,newY);
		testObject* newObject = new testObject();
		(*newObject).setPos(worldMPos);
		if (GetRandomValue(1, 2) == 1) 
		{
			(*newObject).collider.type = shapeType::AABB;
			(*newObject).collider.aabbData.height = 1.f;
			(*newObject).collider.aabbData.width = 1.f;
		}
		else 
		{
			(*newObject).collider.type = shapeType::CIRCLE;
			(*newObject).collider.circleData.radius = 0.5f;
		}

		/*(*newObject).collider.type = shapeType::CIRCLE;
		(*newObject).collider.circleData.radius = 0.5f;*/

		gameObjects.push_back(newObject);
		curWait = 0;
	}
	curWait += GetFrameTime();
	if (IsMouseButtonPressed(0))
	{
		glm::vec2 mousePos(GetMousePosition().x, GetMousePosition().y);
		glm::vec2 worldMPos = screenToWorld(mousePos);
		testObject* newObject = new testObject();
		newObject->setPos(worldMPos);
		newObject->collider.type = shapeType::AABB;
		newObject->collider.aabbData.height = 1.f;
		newObject->collider.aabbData.width = 1.f;
		gameObjects.push_back(newObject);
	}

	if (IsMouseButtonPressed(1))
	{
		glm::vec2 mousePos(GetMousePosition().x, GetMousePosition().y);
		glm::vec2 worldMPos = screenToWorld(mousePos);
		testObject* newObject = new testObject();
		newObject->setPos(worldMPos);
		newObject->collider.type = shapeType::CIRCLE;
		newObject->collider.circleData.radius = 0.5f;
		gameObjects.push_back(newObject);
	}

	if (IsMouseButtonPressed(2))
	{
		glm::vec2 mousePos(GetMousePosition().x, GetMousePosition().y);
		glm::vec2 worldMPos = screenToWorld(mousePos);
		testObject* newObject = new testObject();
		newObject->setPos(worldMPos);
		newObject->collider.type = shapeType::AABB;
		newObject->collider.aabbData.height = 1.f;
		newObject->collider.aabbData.width = 1.f;
		newObject->isStatic = true;
		gameObjects.push_back(newObject);
	}


	ChangeScreenSize(GetScreenHeight() + GetMouseWheelMove()*10);

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