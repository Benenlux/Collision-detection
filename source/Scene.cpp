#include "Scene.h"

Scene::Scene() {
	shader.Create(RESOURCE_DIR "/VertexShader.glsl", RESOURCE_DIR "/FragmentShader.glsl");
	sceneShader = shader.m_shaderProgram;
	AddModel(0.5f, 0.5f, 0.0f, 0.0f);
}

Scene::~Scene() {
	modelsIB.Delete();
	modelsVB.Delete();
	modelsVA.~VertexArray();
	
}

void Scene::AddModel(float height, float width, float x_coord, float y_coord) {
	Model::CreateCube(height, width, x_coord, y_coord);
	m_models.push_back(*this);
	
	
}

void Scene::RenderObjects() {
	BindObjects();
}

void Scene::BindObjects() {
}

void Scene::RenderAll() {

}

void Scene::RenderTerrain() {

}