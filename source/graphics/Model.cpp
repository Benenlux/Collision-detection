#include "Model.h"

Model::Model(std::vector<float> vertices, std::vector<unsigned int> indices, Shader shader, Properties properties){
	m_shader = shader;
	m_vertices = vertices;
	m_indices = indices;
	rb.properties = properties;
}

void Model::CreateVertexBuffer() {
	vb.Create(m_vertices.data(), m_vertices.size());
}

void Model::CreateIndexBuffer() {
	ib.Create(m_indices.data(), m_indices.size());
}



void Model::Render() {
	

	m_shader.BindUniform3f("translation", m_translation);
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0);
}