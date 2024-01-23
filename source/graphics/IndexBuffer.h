#pragma once

#include <glad/glad.h>

class IndexBuffer {
private:
	unsigned int m_RenderID1;
	unsigned int m_count;

public:

	void Bind() const;
	void Unbind() const;
	void Create(const unsigned int* data, unsigned int count);
	void Delete();

	inline unsigned int GetCount() const { return m_count; }
};
