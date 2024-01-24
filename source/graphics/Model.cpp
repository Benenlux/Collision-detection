#include "Model.h"

void Model::CreateVertexBuffer() {
	vb.Create(m_vertices.data(), m_vertices.size());
}

void Model::CreateIndexBuffer() {
	ib.Create(m_indices.data(), m_indices.size());
}

void Model::CreateCube(float height, float width, Shader shader) {
	m_shader = shader;
	m_height = height;
	m_width = width;
	m_vertices = {
		-width / 2, height / 2, 0.0f, // top left
		-width / 2, -height / 2, 0.0f, // bottom left
		width / 2, -height / 2, 0.0f, // bottom right
		width / 2, height / 2, 0.0f, // top right
	};
	m_indices = {
		0, 1, 2,
		0, 3, 2
	};
	va.Bind();
	layout.Push<float>(3);
	CreateVertexBuffer();
	va.AddBuffer(vb, layout);
	CreateIndexBuffer();

	
}

void Model::Render() {
	va.Bind();
	rb.Update();
	glm::mat4 m_scale = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
	m_translation += rb.GetVelocity();
	m_shader.BindUniform3f("translation", m_translation);
	m_shader.BindMat4("scale", m_scale);
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0);
	m_boundingBox = glm::vec2(m_translation.x - m_width / 2, m_translation.y - m_height / 2);
}