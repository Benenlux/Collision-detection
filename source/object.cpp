#include "object.h"

Object::Object(std::vector<float> verticesIn, std::vector<unsigned int> indicesIn, glm::vec3 offsetIn, float massIn) {
	vertices = verticesIn;
	indices = indicesIn;
	offset = offsetIn;
	mass = massIn;
	dimensions = glm::vec3(
		vertices[0] - vertices[9],
		vertices[1] - vertices[10],
		vertices[3] - vertices[11]
	);
}

void Object::CreateBuffer() {
	
	glGenVertexArrays(1, &AttributeBuffer);
	glGenBuffers(1, &VertexBuffer);
	glGenBuffers(1, &IndexBuffer);

	glBindVertexArray(AttributeBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}

void Object::getPosition() {
	position = glm::vec3(
		(vertices[0] + vertices[9]) + offset.x,
		(vertices[1] + vertices[7]) + offset.y,
		(vertices[2] + vertices[11]) + offset.z);
}
