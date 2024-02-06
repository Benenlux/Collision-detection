#include "Model.h"



void Model::CreateCube(float height, float width, float x_coordinate, float y_coordinate) {
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

void Model::Update(float deltaTime) {
	if (has_physics) {
		translate = translate + RigidBody::Update(deltaTime);
	}
	m_vertices = {
		top_left.x + translate.x, top_left.y + translate.y,
		bottom_left.x + translate.x, bottom_left.y + translate.y,
		bottom_right.x + translate.x, bottom_right.y + translate.y,
		top_right.x + translate.x, top_right.y + translate.y
	};

}