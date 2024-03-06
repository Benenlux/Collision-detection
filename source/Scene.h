#pragma once

#include <vector>
#include "graphics/Object.h"
#include "graphics/VertexArray.h"
#include "graphics/VertexBuffer.h"
#include "graphics/VertexBufferLayout.h"
#include "graphics/IndexBuffer.h"
#include "graphics/Shader.h"
#include "physics/Colliders.h"

class Scene : Collider {
private: 
	std::vector<float> objects_vertices;
	std::vector<unsigned int> objects_indices;

	VertexBufferLayout objects_layout;
	
	VertexBuffer objectsVB;
	VertexArray objectsVA;
	IndexBuffer objectsIB;

	unsigned scene_shader;
	float delta_time = 0.0f;
	int index_offset = 0;
	
	
public:
	Shader shader;
	
	bool is_paused = false;
	std::vector<Object> scene_objects;

	Scene();
	~Scene();
	void AddCircle(float radius, float x_coord, float y_coord, int segments);

	//Update functions
	void UpdateObject(Object* object, int object_number);

	//Misc functions
	void Pause();
	void Play();

	//Render functions
	void Render();
	void RenderObjects();
};