#include "gameObject.h"
#include "baseGame.h"
gameObject::gameObject()
{
	
}

void gameObject::Tick()
{
	if (position().y > 30) 
	{
		destroy(this);
	}
}

void gameObject::FixedTick()
{
	
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
		DrawCircle(screenPos.x, screenPos.y, collider.circleData.radius * baseGame::screenSizeMultiplier, BLACK);
		break;
	case shapeType::AABB:
		DrawRectangle(
			//screenPos.x, screenPos.y,
			(position().x - collider.aabbData.width * 0.5f) * baseGame::screenSizeMultiplier,
			(position().y - collider.aabbData.height * 0.5f) * baseGame::screenSizeMultiplier,
			collider.aabbData.width * baseGame::screenSizeMultiplier, collider.aabbData.height * baseGame::screenSizeMultiplier,
			BLACK);
		break;
	default:
		DrawPixel(screenPos.x, screenPos.y, RED);
		break;
	}
}


//called when a collision is happening
void gameObject::OnCollision(physObject other)
{
	std::cout << "C\n";
}

void gameObject::destroy(gameObject* toDestroy) 
{
	for (int i = 0; i < baseGame::gameObjects.size(); i++) 
	{
		if (&baseGame::gameObjects[i] == toDestroy) 
		{
			baseGame::gameObjects.erase(baseGame::gameObjects.begin() + i);
			break;
		}
	}
}