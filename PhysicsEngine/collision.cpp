#include "collision.h"

#pragma region CollisionDetection

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

collision::collision(physObject* o1, physObject* o2) 
{
	object1 = o1;
	object2 = o2;
}
#pragma endregion

#pragma region CollisionResolution
glm::vec2 collision::depenetrateCircleCircle(const glm::vec2& posA, const shape& shapeA, const glm::vec2& posB, const shape& shapeB, float& pen)
{
	float dist = glm::length(posA - posB);
	float sum = shapeA.circleData.radius + shapeB.circleData.radius;

	pen = sum - dist;

	return glm::normalize(posA - posB);
}

glm::vec2 collision::depenetrateAabbCircle(const glm::vec2& posA, const shape& shapeA, const glm::vec2& posB, const shape& shapeB, float& pen)
{
	glm::vec2 normal(0, 0);
	if (shapeA.type == shapeType::CIRCLE) 
	{
		glm::vec2 clampedCPos = glm::clamp(posA,
			glm::vec2(posB.x - shapeB.aabbData.width * 0.5f, posB.y - shapeB.aabbData.height * 0.5f),
			glm::vec2(posB.x + shapeB.aabbData.width * 0.5f, posB.y + shapeB.aabbData.height * 0.5f)
		);
		normal = posA - posB;
		pen = shapeA.circleData.radius - glm::distance(posA, clampedCPos);
	}
	else
	{
		glm::vec2 clampedCPos = glm::clamp(posB,
			glm::vec2(posA.x - shapeA.aabbData.width * 0.5f, posA.y - shapeA.aabbData.height * 0.5f),
			glm::vec2(posA.x + shapeA.aabbData.width * 0.5f, posA.y + shapeA.aabbData.height * 0.5f)
		);
		normal = posA - posB;
		pen = shapeB.circleData.radius - glm::distance(posB, clampedCPos);
	}
	return normal;
}

glm::vec2 collision::depenetrateAabbAabb(const glm::vec2& posA, const shape& shapeA, const glm::vec2& posB, const shape& shapeB, float& pen)
{
	float xDist = glm::abs(posA.x - posB.x);
	float yDist = glm::abs(posA.y - posB.y);
	float xSum = (shapeA.aabbData.width + shapeB.aabbData.width) / 2;
	float ySum = (shapeA.aabbData.height + shapeB.aabbData.height) / 2;

	float xOffset = xSum - xDist;
	float yOffset = ySum - yDist;

	glm::vec2 normal;
	if (xOffset < yOffset)
	{
		pen = xOffset;
		normal = glm::vec2(1,0);
		if (posA.x < posB.x) 
		{
			normal = glm::vec2(-1, 0);
		}
	}
	else 
	{
		pen = yOffset;
		normal = glm::vec2(0, 1);
		if (posA.y < posB.y)
		{
			normal = glm::vec2(0, -1);
		}
	}


	return normal;
}



#pragma endregion
