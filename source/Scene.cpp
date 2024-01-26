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
	modelsVA.Bind();
	modelsLayout.Push<float>(2);
	for (int i = 0; i < m_models.size(); i++) {
		for (int j = 0; j < m_models[i].m_vertices.size(); j++) {
			modelsVertices.push_back(m_models[i].m_vertices[i]);
		}
	}
}

void Scene::RenderAll() {

}

void Scene::RenderTerrain() {

}