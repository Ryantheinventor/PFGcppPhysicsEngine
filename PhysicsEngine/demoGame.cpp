#include "demoGame.h"

void demoGame::onTick() 
{

}

void demoGame::onDraw() const
{
	ClearBackground(RAYWHITE);
	DrawText("Hello Physics", 320, 200, 20, RED);
	
}