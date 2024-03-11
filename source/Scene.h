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
	VertexBufferLayout objects_color_layout;
	
	VertexBuffer objectsVB;
	unsigned int objectsVA;
	IndexBuffer objectsIB;

	unsigned scene_shader;
	float* m_delta_time;
	int index_offset = 0;
	float* m_ratio;
	
	
public:
	Shader shader;
	
	bool is_paused = false;
	std::vector<Object> scene_objects;

	Scene(float* ratio, float* deltaTime);
	~Scene();
	void AddCircle(float radius, float x_coord, float y_coord, int segments, glm::vec3 color);

	//Update functions
	void UpdateObject(Object* object, int object_number);

	//Misc functions
	void Pause();
	void Play();

	//Render functions
	void Render(float ratio, float deltaTime);
	void RenderObjects();
};