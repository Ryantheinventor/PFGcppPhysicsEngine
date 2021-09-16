#include "gameObject.h"
#include "baseGame.h"
gameObject::gameObject()
{
	
}

void gameObject::Tick()
{

}

void gameObject::FixedTick()
{
	
}

void gameObject::OnDraw() const
{
	glm::vec2 screenPos = baseGame::worldToScreen(position());
	DrawCircle(screenPos.x, screenPos.y, 5, BLACK);
}
