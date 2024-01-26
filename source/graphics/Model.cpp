#include "Model.h"



void Model::CreateCube(float height, float width, float x_coordinate, float y_coordinate) {
	position = glm::vec2(x_coordinate, y_coordinate);
	m_height = height;
	m_width = width;
	float width_half = width / 2;
	float height_half = height / 2;
	glm::vec2 top_left = glm::vec2(-width_half + x_coordinate, height_half + y_coordinate);
	glm::vec2 top_right = glm::vec2(width_half + x_coordinate, height_half + y_coordinate);
	glm::vec2 bottom_left = glm::vec2(-width_half + x_coordinate, -height_half + y_coordinate);
	glm::vec2 bottom_right = glm::vec2(width_half + x_coordinate, -height_half + y_coordinate);
	m_vertices = {
		top_left.x, top_left.y,
		bottom_left.x, bottom_left.y,
		bottom_right.x, bottom_right.y,
		top_left.x, top_left.y,
		top_right.x, top_right.y,
		bottom_right.x, bottom_right.y
	};
}

void Model::Render() {
}