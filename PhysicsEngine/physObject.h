#pragma once
#include "glm/glm.hpp"
#include "shape.h"
class physObject
{
private:
	glm::vec2 aForce = glm::vec2(0.f, 0.f);
	glm::vec2 aIForce = glm::vec2(0.f, 0.f);
	glm::vec2 aAccel = glm::vec2(0.f, 0.f);

	glm::vec2 interpolatedPos_ = glm::vec2(0.f, 0.f);
	glm::vec2 physPos = glm::vec2(0.f, 0.f);
	glm::vec2 vel_ = glm::vec2(0.f, 0.f);

public:
	glm::vec2 position() const { return interpolatedPos_; }
	glm::vec2 physicsPosition() const { return physPos; }
	glm::vec2 vel() const { return vel_; }
	
	float mass = 1.f;
	bool hasGravity = true;
	float drag = 3.f;
	bool isStatic = false;

	shape collider;

	physObject();

	void tickPhys(float delta);
	void addForce(glm::vec2 force);
	void addImpulse(glm::vec2 force);
	void addAccel(glm::vec2 accel);
	void addVelocity(glm::vec2 velocity);
	void interpolate(float alpha);
	void setPos(glm::vec2 newPos);
	void collisionStay(physObject other);
	void collisionStart(physObject other);
	void collisionEnd(physObject other);
	void virtual OnCollisionStay(physObject other) {};
	void virtual OnCollisionStart(physObject other) {};
	void virtual OnCollisionEnd(physObject other) {};
};

float resolveCollision(glm::vec2 posA, glm::vec2 velA, float massA,
	glm::vec2 posB, glm::vec2 velB, float massB,
	float elasticity, glm::vec2 normal);

void resolvePhysBodies(physObject& lhs, physObject& rhs, float elasticity, const glm::vec2& normal, float pen);
