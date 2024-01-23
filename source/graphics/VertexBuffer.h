#pragma once

#include <glad/glad.h>

class VertexBuffer {
private:
	unsigned int m_RenderID;

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Create(const void* data, unsigned int size);
	void Bind() const;
	void Unbind() const;

};
