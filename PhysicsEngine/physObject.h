#pragma once
#include "glm/glm.hpp"
class physObject
{
	glm::vec2 pos;
	glm::vec2 vel;
	
	physObject();

	void tickPhys(float delta);
};

