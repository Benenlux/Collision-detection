#include "RigidBody.h"



glm::vec2 RigidBody::Update(float deltaTime) {

	force.y =+ -9.81f * mass;
	
	force * 0.0000001f;
	velocity =+ force / mass;
	return GetVelocity();
}

glm::vec3 RigidBody::GetVelocity() {
	return velocity/dt;
}