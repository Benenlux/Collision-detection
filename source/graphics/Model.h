#pragma once

#include <vector>
#include <optional>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "../physics/Rigidbody.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


//Reason why model exists is to store the vertices and indices of the model
//And to pass them to rigidbodies
// 
// 
//TODO: Model will simply contain the coordinates, which are then passed to the vertex buffer, same for the indices
class Model : public RigidBody {
public:
	std::vector<float> m_vertices;
	std::optional<std::vector<unsigned int>> m_indices;
	glm::vec2 position = glm::vec2(0.0f, 0.0f);

	void Model::CreateCube(float height, float width, float x_coordinate, float y_coordinate);

	//Index and vertex buffers are handled by the scene
	
	//TODO: Add a render function which calls the update function from rigidbody
	void Model::Render();

private:
	

	float m_height;
	float m_width;

	
};