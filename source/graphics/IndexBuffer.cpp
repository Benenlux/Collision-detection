#include "IndexBuffer.h"



void IndexBuffer::Create(const unsigned int* data, unsigned int count)
{
	m_count = count;
	glGenBuffers(1, &m_RenderID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);

}

void IndexBuffer::Delete() {
	glDeleteBuffers(1, &m_RenderID);
}

void IndexBuffer::Bind() const{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
}

void IndexBuffer::Unbind() const{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
}

void IndexBuffer::Update(const unsigned int* data, unsigned int count) {
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_DYNAMIC_DRAW);
}