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

class Model : public RigidBody {
public:
	RigidBody rb;
	
	float scale = 1.0f;
	glm::vec3 m_translation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec2 m_boundingBox;

	void Model::CreateCube(float height, float width, Shader shader);
	void Model::CreateVertexBuffer();
	void Model::CreateIndexBuffer();
	void Model::Render();

private:
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;
	Shader m_shader;
	VertexBuffer vb;
	VertexArray va;
	IndexBuffer ib;
	VertexBufferLayout layout;

	float m_height;
	float m_width;

	
};