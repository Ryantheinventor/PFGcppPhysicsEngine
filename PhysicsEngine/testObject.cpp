#include "testObject.h"

testObject::testObject() 
{

}


void testObject::Tick()
{
	if (position().y > 30)
	{
		destroy(this);
	}
}

void testObject::OnDraw() const
{
	glm::vec2 screenPos = baseGame::worldToScreen(position());
	switch (collider.type)
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

void testObject::OnCollisionStart(physObject other)
{
	drawColor = RED;
	objectsIn++;
}

//called when a collision is happening
void testObject::OnCollisionStay(physObject other)
{
	drawColor = RED;
}

void testObject::OnCollisionEnd(physObject other)
{
	objectsIn--;
	if (objectsIn == 0)
	{
		drawColor = BLACK;
	}
}