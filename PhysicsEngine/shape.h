#pragma once
#include <cstdint>
#include "glm/glm.hpp"
struct circle
{
	float radius = 5;
};

struct aabb
{
	float width = 10;
	float height = 10;
	void getMinMax(const glm::vec2& pos, float& xMin, float& xMax, float& yMin, float& yMax);
};

enum class shapeType : uint8_t
{
	NONE = 0,
	CIRCLE = 1 << 0,
	AABB = 1 << 1
};

struct shape
{
	shape() {};
	shapeType type = shapeType::NONE;

	union
	{
		circle circleData;

		aabb aabbData;
	};

};


