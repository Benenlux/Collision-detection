#include "RigidBody.h"



void RigidBody::Update() {
	dt = glfwGetTime() - dt;

	velocity.y -= 9.81 * dt;
	

}

glm::vec3 RigidBody::GetVelocity() {
	return velocity/dt;
}