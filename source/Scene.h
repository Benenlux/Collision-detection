#pragma once

#include <vector>
#include "graphics/Model.h"
#include "graphics/VertexArray.h"
#include "graphics/VertexBuffer.h"
#include "graphics/VertexBufferLayout.h"
#include "graphics/IndexBuffer.h"
#include "graphics/shader.h"

class Scene : private Model {
private: 
	//To handle collission, we need to store the models in a vector so we can loop through them 
	//Check for their coordinates, and then check if they are colliding
	//I can do this through the translation vector, which is stored in the model class
	//Models and terrain is stored in seperate vectors, because collission behavior is different for both
	std::vector<Model> m_models;
	std::vector<Model> m_terrain;

	
	VertexBufferLayout terrainLayout;
	VertexBuffer terrainVB;
	VertexArray terrainVA;
	IndexBuffer terrainIB;


	//TODO: Add a function to add models to the scene, and parse them correctly to the buffers 
	//Model buffers will be dynamic, so the vertices can be directly updated through the Model class. 

	VertexBufferLayout modelsLayout;
	
	VertexBuffer modelsVB;
	VertexArray modelsVA;
	IndexBuffer modelsIB;

	Shader shader;

	float deltaTime = 0.0f;

public:
	unsigned sceneShader;
	std::vector<float> models_vertices;
	std::vector<unsigned int> models_indices;

	Scene();
	~Scene();
	void AddModel(float height, float width, float x_coord, float y_coord);

	void Init();
	void UpdateObjects();

	void RenderAll(float time);
	//Iterates through the models list, checks for collissions and calls the render function for each model
	//If there is a collission, call the collission function from the rigidbody class
	void RenderObjects();
	void RenderTerrain();
};