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
	
private:
	
	glm::vec3 RigidBody::GetVelocity();
	glm::vec2 force = glm::vec2(0.0f, 0.0f);
	float mass = 1;
};