#pragma once

#include <vector>


#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "../physics/Rigidbody.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Model {
public:
	RigidBody rb;
	VertexBuffer vb;
	VertexArray va;
	IndexBuffer ib;
	float scale = 1.0f;
	glm::vec3 m_translation = glm::vec3(0.0f, 0.0f, 0.0f);

	Model(std::vector<float> vertices, std::vector<unsigned int> indices, Shader shader, VertexBufferLayout layout, int pointCount);
	void CreateVertexBuffer();
	void CreateIndexBuffer();
	void Render();
private:
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;
	Shader m_shader;
};