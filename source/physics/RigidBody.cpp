#include "RigidBody.h"

void RigidBody::SetGravity(bool gravityEnabled) {
	properties.gravityEnabled = gravityEnabled;
}

void RigidBody::Update() {
	dt = glfwGetTime() - dt;
	
	if (properties.gravityEnabled) {
		velocity.y -= 9.81 * dt* properties.scale;
	}

}

glm::vec3 RigidBody::GetVelocity() {
	return velocity/dt;
}