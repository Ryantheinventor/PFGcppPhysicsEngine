#include "gameObject.h"
#include "baseGame.h"
gameObject::gameObject()
{
	
}

void gameObject::Tick()
{
	if (position().y > 100) 
	{
		//should destroy here
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
			screenPos.x, screenPos.y, 
			collider.aabbData.width * baseGame::screenSizeMultiplier, collider.aabbData.height * baseGame::screenSizeMultiplier,
			BLACK);
		break;
	default:
		DrawPixel(screenPos.x, screenPos.y, RED);
		break;
	}
}

void gameObject::OnCollision(physObject other)
{
	std::cout << "Collision\n";
}