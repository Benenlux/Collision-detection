#pragma once

#include <vector>

#include "../physics/Rigidbody.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class Model
{
public:
	RigidBody rb;

	Model(std::vector<float> vertices, std::vector<unsigned int> indices);
	~Model();
	void Render();

private:
};