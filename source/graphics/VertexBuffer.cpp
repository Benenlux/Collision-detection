#include "VertexBuffer.h"



void VertexBuffer::Create(const void* data, unsigned int size) {
	glGenBuffers(1, &m_RenderID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), data, GL_STATIC_DRAW);

}



void VertexBuffer::Delete() {
	glDeleteBuffers(1, &m_RenderID);
}

void VertexBuffer::Bind() const{
	glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
}

void VertexBuffer::Unbind() const{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Update(const void* data, unsigned int size) {
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), data, GL_STATIC_DRAW);
}