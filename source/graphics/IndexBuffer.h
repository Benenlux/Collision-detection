#pragma once

#include <glad/glad.h>


//TODO: Add a function to add indices to the index buffer
class IndexBuffer {
private:
	
	unsigned int m_count;
	unsigned int m_RenderID;

public:
	

	void Bind() const;
	void Unbind() const;
	void Create(const unsigned int* data, unsigned int count);
	void UpdateSize(const unsigned int* data, unsigned int count);
	void Delete();

	inline unsigned int GetCount() const { return m_count; }
};
