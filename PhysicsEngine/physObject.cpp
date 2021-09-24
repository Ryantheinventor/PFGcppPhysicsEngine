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
	if (isStatic) 
	{
		vel_ = glm::vec2(0.f, 0.f);
	}
	else 
	{
		//integrate velocity into position
		physPos += vel_ * delta;
	}
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

void physObject::collisionStay(physObject other)
{
	//handle collsion
	OnCollisionStay(other);
}

void physObject::collisionStart(physObject other)
{
	//handle collsion
	OnCollisionStart(other);
}

void physObject::collisionEnd(physObject other)
{
	//handle collsion
	OnCollisionEnd(other);
}

float resolveCollision(glm::vec2 posA, glm::vec2 velA, float massA, glm::vec2 posB, glm::vec2 velB, float massB, float elasticity, glm::vec2 normal)
{
	glm::vec2 relativeVec = velA - velB;
	float impulseMag = glm::dot(-(1.f + elasticity) * relativeVec, normal) /
					   glm::dot(normal, normal * (1 / massA + 1 / massB));

	return impulseMag;
}

void resolvePhysBodies(physObject& lhs, physObject& rhs, float elasticity, const glm::vec2& normal, float pen) 
{
	
	float impulseMag = resolveCollision(lhs.physicsPosition(), lhs.vel(), lhs.mass,
										rhs.physicsPosition(), rhs.vel(), rhs.mass,
										elasticity, normal);
	glm::vec2 impulse = impulseMag * normal;
	

	
	if (!(lhs.isStatic || rhs.isStatic)) 
	{
		pen *= .51f;
	}
	glm::vec2 correction = normal * pen;

	if (!lhs.isStatic)
	{
		lhs.setPos(lhs.physicsPosition() + correction);
		lhs.addImpulse(impulse);
	}
	if (!rhs.isStatic)
	{
		rhs.setPos(rhs.physicsPosition() - correction);
		rhs.addImpulse(-impulse);
	}
	


}
