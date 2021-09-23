#pragma once
#include "physObject.h"
#include "raylib/raylib.h"
class gameObject : public physObject
{
public:
	gameObject() {};
	void virtual Tick() {};
	void virtual FixedTick() {};
	void virtual OnDestroy() {};
	void virtual OnDraw() const {};
	void destroy(gameObject* toDestroy);
};

