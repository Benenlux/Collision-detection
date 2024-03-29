#include "VertexArray.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_RenderID);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_RenderID);

}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	Bind();
	vb.Bind();

	const auto& elements = layout.GetElements();
	unsigned int index_offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)index_offset);
		index_offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}

	glEnableVertexAttribArray(0);
	
}

void VertexArray::Bind() const {
	glBindVertexArray(m_RenderID);
}

void VertexArray::Unbind() const {
	glBindVertexArray(0);
}