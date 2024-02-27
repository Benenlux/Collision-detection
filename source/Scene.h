#pragma once

#include <vector>
#include "graphics/Object.h"
#include "graphics/VertexArray.h"
#include "graphics/VertexBuffer.h"
#include "graphics/VertexBufferLayout.h"
#include "graphics/IndexBuffer.h"
#include "graphics/shader.h"
#include "physics/Colliders.h"
#include <thread>


class Scene : Collider {
private: 

	std::vector<float> objects_vertices;
	std::vector<unsigned int> objects_indices;

	VertexBufferLayout objects_layout;
	
	VertexBuffer objectsVB;
	VertexArray objectsVA;
	IndexBuffer objectsIB;

	

	unsigned sceneShader;
	float deltaTime = 0.0f;
	
	
public:
	Shader shader;
	int index_offset = 0;
	bool isPaused = false;

	std::vector<Object> objects;

	Scene();
	~Scene();
	void Init();
	void AddSquare(float height, float width, float x_coord, float y_coord);
	void AddCircle(float radius, float x_coord, float y_coord, int segments);

	//Update functions
	void UpdateObjects();
	void CheckCollision(Object* object1, Object* object2);
	void Pause();
	void Play();

	void StressTest(float fps);

	//Render functions
	void Render(float time);
	void RenderObjects();
};