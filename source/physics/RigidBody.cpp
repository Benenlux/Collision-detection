#include "RigidBody.h"



glm::vec2 RigidBody::Update(float deltaTime){
	dt = deltaTime;
	force.y = -9.81f * mass;
	force * 0.000000001f;
	velocity =+ mass / force;

	//If the force in the x direction is 0, velocity turns into inf, this is a fix for that, albeit temporary
	if (std::isinf(velocity.x) != 0) {
		velocity.x = 0;
	}
	
	return velocity*dt;
}

glm::vec3 RigidBody::GetVelocity() {
	return glm::vec3(0.0f, 0.0f, 0.0f);
}