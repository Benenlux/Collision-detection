#pragma once

#include <vector>
#include <optional>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "../physics/Rigidbody.h"
#include "../physics/Transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


enum class Shape {
	SQUARE,
	CIRCLE
};

class Object : public RigidBody{
public:

	bool isOnGround = false;
	float height;
	float width;
	float radius;

	Shape shape;
	std::vector<float> m_vertices;
	

	Transform transform;

	void CreateSquare(float height, float width, float x_coordinate, float y_coordinate);
	void CreateCircle(float radius, float x_coord, float y_coord, int segments);
private: 
	
	glm::vec2 middle_point;
};