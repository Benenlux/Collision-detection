#include "Model.h"

Model::Model(std::vector<float> vertices, std::vector<unsigned int> indices, Shader shader, VertexBufferLayout layout, int pointCount){
	m_shader = shader;
	m_vertices = vertices;
	m_indices = indices;
	va.Bind();
	layout.Push<float>(3);
	CreateVertexBuffer();
	va.AddBuffer(vb, layout);
	CreateIndexBuffer();
}

void Model::CreateVertexBuffer() {
	vb.Create(m_vertices.data(), m_vertices.size());
}

void Model::CreateIndexBuffer() {
	ib.Create(m_indices.data(), m_indices.size());
}



void Model::Render() {
	va.Bind();
	rb.Update();
	glm::mat4 m_scale = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
	m_translation += rb.GetVelocity();
	m_shader.BindUniform3f("translation", m_translation);
	m_shader.BindMat4("scale", m_scale);
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0);
}