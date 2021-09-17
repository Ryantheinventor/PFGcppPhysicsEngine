#pragma once
#include "physObject.h"
class gameObject : public physObject
{
public:
	gameObject();

	void Tick();
	void FixedTick();
	void OnDraw() const;
	void OnCollision(physObject other) override;
};

