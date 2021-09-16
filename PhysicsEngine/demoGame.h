#pragma once
#include "baseGame.h"
class demoGame : public baseGame
{
public:
	void onTick() override;
	void onDraw() const override;
};

