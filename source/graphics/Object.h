#pragma once

#include <vector>
#include <glm/glm.hpp>

class Object{
public:

	bool is_on_ground = false;
	bool is_on_end = false;
	float radius;

	int m_segments;

	std::vector<float> m_vertices;
	
	glm::vec2 position = glm::vec2(0.0f, 0.0f);
	glm::vec3 m_color = glm::vec3(1.0f, 1.0f, 1.0f);

	void Translate(float x, float y);
	void CreateCircle(float radius, float x_coord, float y_coord, int segments, glm::vec3 color);
};