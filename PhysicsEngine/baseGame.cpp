#include "baseGame.h"

float baseGame::screenSizeMultiplier = 30.f;//the number of pixels a single unit will be represented by
std::vector<gameObject> baseGame::gameObjects = std::vector<gameObject>();
baseGame::baseGame() 
{
	map[static_cast<collisionPair>(shapeType::CIRCLE | shapeType::CIRCLE)] = collision::checkCircleCircle;
	map[static_cast<collisionPair>(shapeType::AABB | shapeType::AABB)] = collision::checkAabbAabb;
	map[static_cast<collisionPair>(shapeType::AABB | shapeType::CIRCLE)] = collision::checkAabbCircle;

	

	//physics timings
	targetFixedStep = 0.016f;
	maxAccumulatedTime = 0.16f;
	accumulatedFixedTime = 0.f;//should always start at zero
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
	for (int i = 0; i < baseGame::gameObjects.size(); i++) 
	{
		baseGame::gameObjects[i].interpolate(0.5f);
	}
	//tick game objects
	for (int i = 0; i < baseGame::gameObjects.size(); i++)
	{
		baseGame::gameObjects[i].Tick();
	}

	onTick();
}

void baseGame::tickFixed()
{
	accumulatedFixedTime -= targetFixedStep;
	for (int i = 0; i < baseGame::gameObjects.size(); i++)
	{
		baseGame::gameObjects[i].tickPhys(targetFixedStep);
	}

	for (auto& i : baseGame::gameObjects)
	{
		for (auto& j : baseGame::gameObjects)
		{
			if (&i != &j && map[static_cast<collisionPair>(i.collider.type | j.collider.type)](
				i.physicsPosition(), i.collider,
				j.physicsPosition(), j.collider
				)) 
			{
				i.collision(j);
				j.collision(i);
			}
		}
	}
	//fixed tick game objects
	for (int i = 0; i < baseGame::gameObjects.size(); i++)
	{
		baseGame::gameObjects[i].FixedTick();
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
	return worldPos * screenSizeMultiplier;
}

glm::vec2 baseGame::screenToWorld(glm::vec2 screenPos)
{
	return screenPos * (1 / screenSizeMultiplier);
}


