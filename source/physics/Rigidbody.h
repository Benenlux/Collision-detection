#pragma once

#include <glm/glm.hpp>

#include "Properties.h"

class RigidBody
{
public:
	Properties properties;

	void SetGravity(bool gravityEnabled);
	glm::vec3 Update();
private:
	glm::vec3 force = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 velocity;

	
};