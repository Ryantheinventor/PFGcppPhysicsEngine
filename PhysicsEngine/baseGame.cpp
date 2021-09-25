#include "baseGame.h"

float baseGame::screenSizeMultiplier = 30.f;//the number of pixels a single unit will be represented by
float baseGame::targetFixedStep = 0.016f;//fixed time step
std::vector<gameObject*> baseGame::gameObjects = std::vector<gameObject*>();
std::vector<gameObject*> baseGame::destroyedGameObjects = std::vector<gameObject*>();
std::vector<collision> baseGame::lastTickCollisions = std::vector<collision>();

baseGame::baseGame() 
{
	//collision detection map
	map[static_cast<collisionPair>(shapeType::CIRCLE | shapeType::CIRCLE)] = collision::checkCircleCircle;
	map[static_cast<collisionPair>(shapeType::AABB | shapeType::AABB)] = collision::checkAabbAabb;
	map[static_cast<collisionPair>(shapeType::AABB | shapeType::CIRCLE)] = collision::checkAabbCircle;

	//depenetration map
	dMap[static_cast<collisionPair>(shapeType::CIRCLE | shapeType::CIRCLE)] = collision::depenetrateCircleCircle;
	dMap[static_cast<collisionPair>(shapeType::CIRCLE | shapeType::AABB)] = collision::depenetrateAabbCircle;
	dMap[static_cast<collisionPair>(shapeType::AABB | shapeType::AABB)] = collision::depenetrateAabbAabb;



	//time between garbage collection where destroyed gameObjects get deleted
	garbageCollectionTime = 10.f;

	//physics timings
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
	std::cout << "\n" << GetFPS() << "FPS " << baseGame::lastTickCollisions.size() << "Collisions\n";
	std::cout << baseGame::gameObjects.size() << "Active:" << baseGame::destroyedGameObjects.size() << "Destroyed\n";
	accumulatedFixedTime += GetFrameTime();
	curGCTime += GetFrameTime();
	if (accumulatedFixedTime > maxAccumulatedTime)
	{
		accumulatedFixedTime = maxAccumulatedTime;
	}
	//aa
	for (int i = 0; i < baseGame::gameObjects.size(); i++) 
	{
		(*baseGame::gameObjects[i]).interpolate(0.5f);
	}
	//tick game objects
	for (int i = 0; i < baseGame::gameObjects.size(); i++)
	{
		(*baseGame::gameObjects[i]).Tick();
	}
	if (curGCTime >= garbageCollectionTime) 
	{
		std::cout << "GC\n";
		//do clean up
		for (int i = baseGame::destroyedGameObjects.size()-1; i >= 0; i--)
		{
			gameObject* go = baseGame::destroyedGameObjects[i];
			bool goodToDelete = true;
			for (collision c : lastTickCollisions)
			{
				if (go == c.object1 || go == c.object2) 
				{
					goodToDelete = false;
				}
			}
			if (goodToDelete) 
			{
				delete baseGame::destroyedGameObjects[i];
				baseGame::destroyedGameObjects.erase(baseGame::destroyedGameObjects.begin() + i);
			}
		}
		curGCTime = 0;
	}
	onTick();
}

void baseGame::tickFixed()
{
	accumulatedFixedTime -= targetFixedStep;
	for (int i = 0; i < baseGame::gameObjects.size(); i++)
	{
		(*baseGame::gameObjects[i]).tickPhys(targetFixedStep);
		(*baseGame::gameObjects[i]).FixedTick();
	}
	//collision detection
	std::vector<collision> collisions;
	for (int iP = 0; iP < baseGame::gameObjects.size(); iP++)
	{
		for (int jP = iP + 1; jP < baseGame::gameObjects.size(); jP++)
		{
			gameObject& i = *baseGame::gameObjects[iP];
			gameObject& j = *baseGame::gameObjects[jP];
			if (i.collider.type != shapeType::NONE && j.collider.type != shapeType::NONE) 
			{
				collisionPair pair = static_cast<collisionPair>(i.collider.type | j.collider.type);
				if (iP != jP && map[pair](
					i.physicsPosition(), i.collider,
					j.physicsPosition(), j.collider
					))
				{
					collision curColl = collision(&i, &j);
					collisions.push_back(curColl);
					//collision stay
					i.collisionStay(j);
					j.collisionStay(i);

					//send collision started if this collision is new
					bool collisionIsNew = true;
					for (int i = baseGame::lastTickCollisions.size() - 1; i >= 0; i--)
					{
						if (((baseGame::lastTickCollisions[i].object1 == curColl.object1) &&
							(baseGame::lastTickCollisions[i].object2 == curColl.object2)
							))
						{
							//remove collisions that have been re confirmed
							baseGame::lastTickCollisions.erase(baseGame::lastTickCollisions.begin() + i);
							collisionIsNew = false;
						}
					}
					if (collisionIsNew)
					{
						//collision start
						(*curColl.object1).collisionStart(*curColl.object2);
						(*curColl.object2).collisionStart(*curColl.object1);
					}

					//collision resolution
					float pen = 0.f;
					glm::vec2 normal = dMap[pair](i.physicsPosition(), i.collider, j.physicsPosition(), j.collider, pen);

					resolvePhysBodies(i, j, 1.f, normal, pen);

				}
			}
			
		}
	}


	//oh god these loops are painfull
	for (int i = baseGame::lastTickCollisions.size() - 1; i >= 0; i--)
	{
		//collision end
		
		(*baseGame::lastTickCollisions[i].object1).collisionEnd(*baseGame::lastTickCollisions[i].object2);
		(*baseGame::lastTickCollisions[i].object2).collisionEnd(*baseGame::lastTickCollisions[i].object1);
		baseGame::lastTickCollisions.erase(baseGame::lastTickCollisions.begin() + i);
	}
	baseGame::lastTickCollisions = collisions;




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
	for (int i = 0; i < baseGame::gameObjects.size(); i++) 
	{
		baseGame::gameObjects[i]->destroy(baseGame::gameObjects[i]);
	}
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

void baseGame::ChangeScreenSize(int windowHeight)
{
	float windowWidth = (windowHeight / 9) * 16;
	screenSizeMultiplier = screenSizeMultiplier * (float)windowHeight / GetScreenHeight();
	SetWindowSize(windowWidth, windowHeight);
}
