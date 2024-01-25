#pragma once

#include <glm/glm.hpp>
#include <iostream>

#include <GLFW/glfw3.h>

class RigidBody {
public:
	float dt = 0.0f;
	glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	

	void Update();
	glm::vec3 RigidBody::GetVelocity();

	// TODO: Add a function which handles collission between this and the other rigidbody
	// The funciton is called through the scene, which then passes the rigidbody from the other model
	// The function will then apply the proper behavior based on this and the other models' rigidbody
private:
	glm::vec3 force = glm::vec3(0.0f, 0.0f, 0.0f);
	
};