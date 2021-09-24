#pragma once
#include "baseGame.h"
class testObject : public gameObject
{
public:
	testObject();
	void Tick() override;
	void FixedTick() override {};
	void OnDestroy() override {};
	void OnDraw() const override;
	void OnCollisionStart(physObject other) override;
	void OnCollisionStay(physObject other) override;
	void OnCollisionEnd(physObject other) override; 

	int objectsIn = 0;
	Color drawColor;


	Color normalColor = BLACK;
	Color collColor = RED;


};

