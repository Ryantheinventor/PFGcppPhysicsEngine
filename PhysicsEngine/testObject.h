#pragma once
#include "baseGame.h"
class testObject : public gameObject
{
public:
	testObject();
	void virtual Tick();
	void virtual FixedTick() {};
	void virtual OnDestroy() {};
	void OnDraw() const;
	void OnCollisionStart(physObject other) override;
	void OnCollisionStay(physObject other) override;
	void OnCollisionEnd(physObject other) override; 

	int objectsIn = 0;
	Color drawColor;
};

