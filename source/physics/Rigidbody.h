#pragma once

#include <glm/glm.hpp>
#include <iostream>


#include "Properties.h"
#include <GLFW/glfw3.h>

class RigidBody
{
public:
	Properties properties;
	float dt = 0.0f;
	glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f);

	void SetGravity(bool gravityEnabled);
	void Update();
	glm::vec3 RigidBody::GetVelocity();
private:
	glm::vec3 force = glm::vec3(0.0f, 0.0f, 0.0f);
	
	
	
};