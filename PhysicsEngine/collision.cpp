#include "collision.h"


bool collision::checkCircleCircle(glm::vec2 posA, circle circleA, glm::vec2 posB, circle circleB)
{
	return glm::distance(posA, posB) < circleA.radius + circleB.radius;
}

bool collision::checkCircleCircle(const glm::vec2& posA, const shape& shapeA, const glm::vec2& posB, const shape& shapeB)
{
	return checkCircleCircle(posA, shapeA.circleData, posB, shapeB.circleData);
}

bool collision::checkAabbAabb(glm::vec2 posA, aabb boxA, glm::vec2 posB, aabb boxB)
{
	return posA.x < posB.x + boxB.width &&
		posA.x + boxA.width > posB.x &&
		posA.y < posB.y + boxB.height &&
		posA.y + boxA.height > posB.y;
		
}

bool collision::checkAabbAabb(const glm::vec2& posA, const shape& shapeA, const glm::vec2& posB, const shape& shapeB)
{
	return checkAabbAabb(posA, shapeA.aabbData, posB, shapeB.aabbData);
}

bool collision::checkAabbCircle(glm::vec2 posA, aabb boxA, glm::vec2 posB, circle circleB)
{
	glm::vec2 clampedCPos = glm::clamp(posB,
		glm::vec2(posA.x - boxA.width * 0.5f, posA.y - boxA.height * 0.5f),
		glm::vec2(posA.x + boxA.width * 0.5f, posA.y + boxA.height * 0.5f)
	);

	return glm::distance(posB, clampedCPos) < circleB.radius;
}

bool collision::checkAabbCircle(const glm::vec2& posA, const shape& shapeA, const glm::vec2& posB, const shape& shapeB)
{
	if (shapeA.type == shapeType::AABB) 
	{
		return checkAabbCircle(posA, shapeA.aabbData, posB, shapeB.circleData);
	}
	else 
	{
		return checkAabbCircle(posB, shapeB.aabbData, posA, shapeA.circleData);
	}
	
}
