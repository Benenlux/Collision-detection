#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <iostream>

struct Transform {
	glm::vec2 position = glm::vec2(0.0f, 0.0f);
	glm::vec2 translation = glm::vec2(0.0f, 0.0f);

	void Translate(float x, float y);
};