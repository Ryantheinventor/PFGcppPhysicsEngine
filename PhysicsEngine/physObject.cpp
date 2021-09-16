#include "physObject.h"

void physObject::tickPhys(float delta) 
{
	pos += vel * delta;
}