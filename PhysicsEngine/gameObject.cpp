#include "gameObject.h"
#include "baseGame.h"

gameObject::gameObject()
{
	drawColor = BLACK;
}

void gameObject::Tick()
{
	if (position().y > 30) 
	{
		destroy(this);
	}
}

void gameObject::OnDraw() const
{
	glm::vec2 screenPos = baseGame::worldToScreen(position());
	switch(collider.type)
	{
	case shapeType::NONE:
		DrawPixel(screenPos.x, screenPos.y, RED);
		break;
	case shapeType::CIRCLE:
		DrawCircle(screenPos.x, screenPos.y, collider.circleData.radius * baseGame::screenSizeMultiplier, drawColor);
		break;
	case shapeType::AABB:
		DrawRectangle(
			//screenPos.x, screenPos.y,
			(position().x - collider.aabbData.width * 0.5f) * baseGame::screenSizeMultiplier,
			(position().y - collider.aabbData.height * 0.5f) * baseGame::screenSizeMultiplier,
			collider.aabbData.width * baseGame::screenSizeMultiplier, collider.aabbData.height * baseGame::screenSizeMultiplier,
			drawColor);
		break;
	default:
		DrawPixel(screenPos.x, screenPos.y, RED);
		break;
	}
}

void gameObject::OnCollisionStart(physObject other)
{
	drawColor = RED;
	objectsIn++;
}

//called when a collision is happening
void gameObject::OnCollisionStay(physObject other)
{
	drawColor = RED;
}

void gameObject::OnCollisionEnd(physObject other)
{
	objectsIn--;
	if (objectsIn == 0) 
	{
		drawColor = BLACK;
	}
}

void gameObject::destroy(gameObject* toDestroy) 
{
	for (int i = 0; i < baseGame::gameObjects.size(); i++) 
	{
		if (baseGame::gameObjects[i] == toDestroy) 
		{
			(*baseGame::gameObjects[i]).OnDestroy();
			baseGame::destroyedGameObjects.push_back(baseGame::gameObjects[i]);
			//delete[] baseGame::gameObjects[i];
			baseGame::gameObjects.erase(baseGame::gameObjects.begin() + i);
			break;
		}
	}
}