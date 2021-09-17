#pragma once
#include "physObject.h"
#include "raylib/raylib.h"
class gameObject : public physObject
{
public:
	gameObject();
	Color drawColor;
	int objectsIn = 0;
	void virtual Tick() ;
	void virtual FixedTick() {};
	void virtual OnDestroy() {};
	void OnDraw() const;
	void OnCollisionStart(physObject other) override;
	void OnCollisionStay(physObject other) override;
	void OnCollisionEnd(physObject other) override;
	void destroy(gameObject* toDestroy);
};

