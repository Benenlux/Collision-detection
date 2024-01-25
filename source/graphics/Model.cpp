#include "Model.h"



void Model::CreateCube(float height, float width, float x_coordinate, float y_coordinate) {
	position = glm::vec2(x_coordinate, y_coordinate);
	m_height = height;
	m_width = width;
	float width_half = width / 2;
	float height_half = height / 2;
	m_vertices = {
		-width_half + position.x,  height_half + position.y,// top left
		-width_half + position.x, -height_half + position.y,// bottom left
		 width_half + position.x, -height_half + position.y,// bottom right
		 width_half + position.x,  height_half + position.y // top right
	};
		
}

void Model::Render() {
}