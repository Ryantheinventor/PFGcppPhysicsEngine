#include "shape.h"



void aabb::getMinMax(const glm::vec2& pos, float& xMin, float& xMax, float& yMin, float& yMax) 
{
	xMin = pos.x - width / 2;
	xMax = pos.x + width / 2;
	yMin = pos.y - height / 2;
	yMax = pos.y + height / 2;
}

