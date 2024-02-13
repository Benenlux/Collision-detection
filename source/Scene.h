#pragma once

#include <vector>
#include "graphics/Object.h"
#include "graphics/VertexArray.h"
#include "graphics/VertexBuffer.h"
#include "graphics/VertexBufferLayout.h"
#include "graphics/IndexBuffer.h"
#include "graphics/shader.h"
#include <thread>

class Scene : private Object {
private: 

	std::vector<float> objects_vertices;
	std::vector<unsigned int> objects_indices;

	VertexBufferLayout objects_layout;
	
	VertexBuffer objectsVB;
	VertexArray objectsVA;
	IndexBuffer objectsIB;

	Shader shader;

	unsigned sceneShader;
	float deltaTime = 0.0f;
	
	
public:
	bool isPaused = false;
	std::vector<std::shared_ptr<Object>> objects;
	Scene();
	~Scene();
	void Init();
	void AddObject(float height, float width, float x_coord, float y_coord);

	void AddCircle(float radius, float x_coord, float y_coord);

	//Update functions
	void UpdateObjects();
	void CheckCollisions();
	void Pause();
	void Play();

	void StressTest(float fps);

	//Render functions
	void RenderAll(float time);
	void RenderObjects();
};