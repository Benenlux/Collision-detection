#pragma once

#include <vector>
#include "graphics/Model.h"
#include "graphics/VertexArray.h"
#include "graphics/VertexBuffer.h"
#include "graphics/VertexBufferLayout.h"
#include "graphics/IndexBuffer.h"
#include "graphics/shader.h"
#include <thread>

class Scene : private Model {
private: 
	
	std::vector<Model> m_terrain;

	std::vector<float> models_vertices;
	std::vector<unsigned int> models_indices;

	VertexBufferLayout terrainLayout;
	VertexBuffer terrainVB;
	VertexArray terrainVA;
	IndexBuffer terrainIB;

	VertexBufferLayout modelsLayout;
	
	VertexBuffer modelsVB;
	VertexArray modelsVA;
	IndexBuffer modelsIB;

	Shader shader;

	unsigned sceneShader;
	float deltaTime = 0.0f;
	std::thread thread1;
	std::thread thread2;
	
	
public:
	bool isPaused = false;
	std::vector<Model> m_models;
	Scene();
	~Scene();
	void Init();
	void AddModel(float height, float width, float x_coord, float y_coord);

	//Update functions
	void UpdateObjects();
	void CheckCollisions(int offset);
	void Pause();
	void Play();

	void StressTest(float fps);

	//Render functions
	void RenderAll(float time);
	void RenderObjects();
	void RenderTerrain();
};