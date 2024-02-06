#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include <cmath>

#include <GLFW/glfw3.h>

class RigidBody {
public:
	float dt = 0.0f;
	glm::vec2 velocity = glm::vec2(0.0f, 0.0f);
	

	glm::vec2 Update(float deltaTime);
	

	// TODO: Add a function which handles collission between this and the other rigidbody
	// The funciton is called through the scene, which then passes the rigidbody from the other model
	// The function will then apply the proper behavior based on this and the other models' rigidbody
private:
	
	glm::vec3 RigidBody::GetVelocity();
	glm::vec2 force = glm::vec2(0.0f, 0.0f);
	float mass = 1;
};