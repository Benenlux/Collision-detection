#include "IndexBuffer.h"



void IndexBuffer::Create(const unsigned int* data, unsigned int count)
{
	m_count = count;
	glGenBuffers(1, &m_RenderID1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);

}

void IndexBuffer::Delete() {
	glDeleteBuffers(1, &m_RenderID1);
}

void IndexBuffer::Bind() const{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID1);
}

void IndexBuffer::Unbind() const{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
}