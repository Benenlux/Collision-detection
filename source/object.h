#pragma once

#include <vector>
#include <glad/glad.h>
#include "glm/glm.hpp"

class Object {
	//note to self: Object will have it's own buffers.
	//note to self: How the fuck am I going to draw 2 objects with different behavior
public:
	//------- Variables used across objects -------//
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	glm::vec3 offset;
	glm::vec3 position;
	float mass;
	float velocity;
	glm::vec3 dimensions;
	unsigned int VertexBuffer, AttributeBuffer, IndexBuffer;

	Object(std::vector<float>, std::vector<unsigned int>, glm::vec3, float);
	void Object::CreateBuffer();
	void Object::getPosition();
private:
	
};