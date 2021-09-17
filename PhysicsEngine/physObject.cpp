#include "physObject.h"

physObject::physObject() 
{

}

void physObject::tickPhys(float delta)
{
	if (hasGravity) 
	{
		addAccel(glm::vec2(0.f,9.8f));
	}
	float tickDrag = drag * delta;
	if (glm::length(vel_) > tickDrag)
	{
		vel_ -= glm::normalize(vel_) * tickDrag;
	}
	else 
	{
		vel_ = glm::vec2(0.f, 0.f);
	}
	//integrate forces into velocity
	//normal force
	vel_ += aForce * delta;
	aForce = glm::vec2(0.f, 0.f);
	//impulse force
	vel_ += aIForce;
	aIForce = glm::vec2(0.f, 0.f);

	//integrate acceleration
	vel_ += aAccel * delta;
	aAccel = glm::vec2(0.f,0.f);

	//integrate velocity into position
	physPos += vel_ * delta;
}

void physObject::addForce(glm::vec2 force)
{
	aForce += force / mass;
}

void physObject::addImpulse(glm::vec2 force)
{
	aIForce += force / mass;
}

void physObject::addAccel(glm::vec2 accel)
{
	aAccel += accel;
}

void physObject::addVelocity(glm::vec2 velocity)
{
	vel_ += velocity;
}

void physObject::interpolate(float alpha)
{
	interpolatedPos_ = glm::mix(interpolatedPos_, physPos, alpha);
}

void physObject::setPos(glm::vec2 newPos) 
{
	physPos = newPos;
	interpolatedPos_ = newPos;
}

void physObject::collision(physObject other) 
{
	//handle collsion
	OnCollision(other);
}

