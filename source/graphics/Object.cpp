#include "Object.h"




void Object::CreateSquare(float inHeight, float inWidth, float x_coordinate, float y_coordinate) {
	shape = Shape::SQUARE;
	height = inHeight;
	width = inWidth;


	transform.Translate(x_coordinate, y_coordinate);
	
	m_vertices = {
		-width, height, //top left 
		width, height, //top right
		width, -height, //bottom right 
		-width, -height //bottom left 
	};
}

void Object::CreateCircle(float inRadius, float x_coord, float y_coord, int segments) {
	shape = Shape::CIRCLE;
	radius = inRadius;

	transform.Translate(x_coord, y_coord);

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

