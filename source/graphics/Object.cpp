#include "Object.h"

void Object::CreateCircle(float inRadius, float x_coord, float y_coord, int segments) {
	radius = inRadius;

	Translate(x_coord, y_coord);

	glm::vec2 middle_point = glm::vec2(0,0);
	float angle = 0.0f;
	m_vertices.push_back(middle_point.x);
	m_vertices.push_back(middle_point.y);

	for (int i = 0; i < segments; i++) {
		float x = middle_point.x + radius * (cos(angle));
		float y = middle_point.y + radius * sin(angle);
		m_vertices.push_back(x);
		m_vertices.push_back(y);
		angle += 2 * 3.14159 / segments;
	}
}

void Object::Translate(float x, float y) {
	position = position + glm::vec2(x, y);
}

