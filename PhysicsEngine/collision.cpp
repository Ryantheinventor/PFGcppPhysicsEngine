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
	float aXmn;
	float aXmx;
	float aYmn;
	float aYmx;

	float bXmn;
	float bXmx;
	float bYmn;
	float bYmx;

	boxA.getMinMax(posA, aXmn, aXmx, aYmn, aYmx);
	boxB.getMinMax(posB, bXmn, bXmx, bYmn, bYmx);

	return aXmn <= bXmx && aXmx >= bXmn && aYmn <= bYmx && aYmx >= bYmn;	
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
	glm::vec2 normal(1, 1);
	glm::vec2 clampedCPos();
	float xDiff = posA.x - posB.x;
	float yDiff = posA.y - posB.y;

	float sumX = 0;
	float sumY = 0;
	if (shapeA.type == shapeType::CIRCLE) 
	{
		sumX = shapeB.aabbData.width / 2 + shapeA.circleData.radius;
		sumY = shapeB.aabbData.height / 2 + shapeA.circleData.radius;
	}
	else 
	{
		sumX = shapeA.aabbData.width / 2 + shapeB.circleData.radius;
		sumY = shapeA.aabbData.height / 2 + shapeB.circleData.radius;
	}

	if (glm::abs(xDiff) > glm::abs(yDiff))
	{
		//moveOnX
		normal = glm::vec2(1, 0);
		if (xDiff < 0) 
		{
			normal *= -1;
		}
		pen = sumX - glm::abs(xDiff);
	}
	else 
	{
		//moveOnY
		normal = glm::vec2(0, 1);
		if (yDiff < 0)
		{
			normal *= -1;
		}
		pen = sumY - glm::abs(yDiff);
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
