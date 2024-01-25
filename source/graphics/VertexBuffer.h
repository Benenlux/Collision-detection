#pragma once

#include <glad/glad.h>

//TODO: Add a function to add vertices to the vertex buffer and update certain vertices
class VertexBuffer {
private:
	unsigned int m_RenderID;

public:
	void Delete();

	void Create(const void* data, unsigned int size);
	void Bind() const;
	void Unbind() const;

};
