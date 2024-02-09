#include "Scene.h"

Scene::Scene() {
	shader.Create(RESOURCE_DIR "/VertexShader.glsl", RESOURCE_DIR "/FragmentShader.glsl");
	sceneShader = shader.m_shaderProgram;
}

Scene::~Scene() {
	modelsIB.Delete();
	modelsVB.Delete();
	modelsVA.~VertexArray();
	
}

void Scene::AddModel(float height, float width, float x_coord, float y_coord) {
	Model model;
	model.CreateCube(height, width, x_coord, y_coord);
	m_models.push_back(model);
	for (int i = 0; i < model.m_vertices.size(); i++) {
		models_vertices.push_back(model.m_vertices[i]);
	}
	
	for (int i = 0; i < 1; i++) {
		int offset = (m_models.size()-1) * 4;
		models_indices.push_back(0 + offset);
		models_indices.push_back(1 + offset);
		models_indices.push_back(2 + offset);
		models_indices.push_back(2 + offset);
		models_indices.push_back(3 + offset);
		models_indices.push_back(0 + offset);
	}
	/*
	modelsVA.Bind();
	modelsVB.Update(models_vertices.data(), models_vertices.size());
	modelsIB.Update(models_indices.data(), models_indices.size());
	*/
}

void Scene::RenderObjects() {
	UpdateObjects();
	modelsVA.Bind();
	glDrawElements(GL_TRIANGLES, models_indices.size(), GL_UNSIGNED_INT, nullptr);
}

void Scene::Init() {	
	modelsVA.Bind();
	modelsVB.Create(models_vertices.data(), models_vertices.size());
	modelsLayout.Push<float>(2);
	modelsVA.AddBuffer(modelsVB, modelsLayout);
	modelsIB.Create(models_indices.data(), models_indices.size());
}

void Scene::UpdateObjects() {
	for (int i = 0; i < m_models.size(); i++) {
		m_models[i].Update(deltaTime);
	}
	models_vertices.clear();
	for (int i = 0; i < m_models.size(); i++) {
		for (int j = 0; j < m_models[i].m_vertices.size(); j++) {
			models_vertices.push_back(m_models[i].m_vertices[j]);
			
		}
	}

	modelsVB.Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, models_vertices.size() * sizeof(GLfloat), models_vertices.data());
}

void Scene::RenderAll(float time){
	deltaTime = time;
	RenderObjects();
}

void Scene::RenderTerrain() {

}