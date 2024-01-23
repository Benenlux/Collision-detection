#pragma once

#include <vector>

#include "../physics/Rigidbody.h"
#include "../physics/Properties.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

class Model {
public:
	RigidBody rb;
	VertexBuffer vb;
	IndexBuffer ib;
	glm::vec3 m_translation = glm::vec3(0.0f, 0.0f, 0.0f);
	float dt; 

	Model(std::vector<float> vertices, std::vector<unsigned int> indices, Shader shader, Properties properties);
	void CreateVertexBuffer();
	void CreateIndexBuffer();
	void Render();
private:
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;
	Shader m_shader;
};