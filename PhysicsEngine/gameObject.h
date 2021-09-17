#pragma once
#include "physObject.h"
class gameObject : public physObject
{
public:
	gameObject();

	void virtual Tick() ;
	void virtual FixedTick();
	void OnDraw() const;
	void OnCollision(physObject other) override;
	void destroy(gameObject* toDestroy);
};

