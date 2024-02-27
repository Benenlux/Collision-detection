#pragma once

#include <vector>
#include <optional>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "../physics/Rigidbody.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Object : public RigidBody{
public:

	bool isOnGround = false;
	float radius;

	std::vector<float> m_vertices;
	
	glm::vec2 position = glm::vec2(0.0f, 0.0f);

	void Translate(float x, float y);
	void CreateCircle(float radius, float x_coord, float y_coord, int segments);
private: 
	
	glm::vec2 middle_point;
};