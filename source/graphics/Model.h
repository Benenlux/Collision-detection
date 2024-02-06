#pragma once

#include <vector>
#include <optional>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "../physics/Rigidbody.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Model : public RigidBody {
public:
	std::vector<float> m_vertices;
	

	void Model::CreateCube(float height, float width, float x_coordinate, float y_coordinate);
	void Model::Update(float deltaTime);
private:
	bool has_physics = true;
	glm::vec2 translate;

	glm::vec2 top_left;
	glm::vec2 top_right;
	glm::vec2 bottom_left;
	glm::vec2 bottom_right;
};