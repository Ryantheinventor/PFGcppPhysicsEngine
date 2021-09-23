#pragma once
#include "glm/glm.hpp"
#include "physObject.h"
class collision
{
public:
	//collision checks
	static bool checkCircleCircle(glm::vec2 posA, circle circleA, glm::vec2 posB, circle circleB);
	static bool checkCircleCircle(const glm::vec2& posA, const shape& shapeA, const glm::vec2& posB, const shape& shapeB);

	static bool checkAabbAabb(glm::vec2 posA, aabb boxA, glm::vec2 posB, aabb boxB);
	static bool checkAabbAabb(const glm::vec2& posA, const shape& shapeA, const glm::vec2& posB, const shape& shapeB);

	static bool checkAabbCircle(glm::vec2 posA, aabb boxA, glm::vec2 posB, circle circleB);
	static bool checkAabbCircle(const glm::vec2& posA, const shape& shapeA, const glm::vec2& posB, const shape& shapeB);
	

	physObject* object1;
	physObject* object2;

	collision(physObject* o1, physObject* o2);

	//collision resolution
	//depen
	static glm::vec2 depenetrateCircleCircle(const glm::vec2& posA, const shape& shapeA, const glm::vec2& posB, const shape& shapeB, float& pen);
	static glm::vec2 depenetrateAabbAabb(const glm::vec2& posA, const shape& shapeA, const glm::vec2& posB, const shape& shapeB, float& pen);
	static glm::vec2 depenetrateAabbCircle(const glm::vec2& posA, const shape& shapeA, const glm::vec2& posB, const shape& shapeB, float& pen);



};
