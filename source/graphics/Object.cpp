#include "Object.h"

Object::Object() {

}

Object::Object(float height, float width, float x_coordinate, float y_coordinate) {
	translate = glm::vec2(x_coordinate, y_coordinate);
	float width_half = width / 2;
	float height_half = height / 2;
	top_left = glm::vec2(-width_half + x_coordinate, height_half + y_coordinate);
	top_right = glm::vec2(width_half + x_coordinate, height_half + y_coordinate);
	bottom_left = glm::vec2(-width_half + x_coordinate, -height_half + y_coordinate);
	bottom_right = glm::vec2(width_half + x_coordinate, -height_half + y_coordinate);

	m_vertices = {
		top_left.x, top_left.y,
		bottom_left.x, bottom_left.y,
		bottom_right.x, bottom_right.y,
		top_right.x, top_right.y
	};
	translate = glm::vec2(0.0f, 0.0f);
}

Object::~Object() {
}

void Object::CreateCube(float height, float width, float x_coordinate, float y_coordinate) {
	translate = glm::vec2(x_coordinate, y_coordinate);
	float width_half = width / 2;
	float height_half = height / 2;
	top_left = glm::vec2(-width_half + x_coordinate, height_half + y_coordinate);
	top_right = glm::vec2(width_half + x_coordinate, height_half + y_coordinate);
	bottom_left = glm::vec2(-width_half + x_coordinate, -height_half + y_coordinate);
	bottom_right = glm::vec2(width_half + x_coordinate, -height_half + y_coordinate);

	m_vertices = {
		top_left.x, top_left.y,
		bottom_left.x, bottom_left.y,
		bottom_right.x, bottom_right.y,
		top_right.x, top_right.y
	};
	translate = glm::vec2(0.0f, 0.0f);
}

void Object::Transform(glm::vec2 transformation) {
	top_left.x = top_left.x + transformation.x;
	top_left.y = top_left.y + transformation.y;
	bottom_left.x = bottom_left.x + transformation.x;
	bottom_left.y = bottom_left.y + transformation.y;
	bottom_right.x = bottom_right.x + transformation.x;
	bottom_right.y = bottom_right.y + transformation.y;
	top_right.x = top_right.x + transformation.x;
	top_right.y = top_right.y + transformation.y;
}

void Object::Update(float deltaTime) {
	if (has_physics) {
		translate = RigidBody::Update(deltaTime);
	}
	
	Transform(translate);
	m_vertices = {
		top_left.x, top_left.y,
		bottom_left.x, bottom_left.y,
		bottom_right.x, bottom_right.y,
		top_right.x, top_right.y
	};
	
}

void Object::CreateCircle(float radius, float x_coord, float y_coord) {
	glm::vec2 middle_point = glm::vec2(x_coord, y_coord);
	float angle = 0.0f;
	float segments = 8;
	m_vertices.push_back(middle_point.x);
	m_vertices.push_back(middle_point.y);
	for (int i = 0; i < segments; i++) {
		float x = middle_point.x + radius * cos(angle);
		float y = middle_point.y + radius * sin(angle);
		m_vertices.push_back(x);
		m_vertices.push_back(y);
		angle += 2 * 3.14159 / segments;
		std::cout << x << "f, " << y << "f," << std::endl;
	}
}