#pragma once
#include "glm/glm.hpp"
#include "physObject.h"
class collision
{
public:
	//collision checks
	static bool checkCircleCircle(glm::vec2 posA, circle circleA, glm::vec2 posB, circle circleB);
	static bool checkCircleCircle(const glm::vec2& posA, const shape& shapeA, const glm::vec2& posB, const shape& shapeB);
	





};
