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
	Model model;
	model.CreateCube(height, width, x_coord, y_coord);
	m_models.push_back(model);
	for (int i = 0; i < model.m_vertices.size(); i++) {
		models_vertices.push_back(model.m_vertices[i]);
	}
	std::cout << "Model added" << std::endl;
}

void Scene::RenderObjects() {
	modelsVA.Bind();
	glDrawElements(GL_TRIANGLES, models_indices.size(), GL_UNSIGNED_INT, nullptr);
}

void Scene::InitObjects() {
	for (int i = 0; i < m_models.size(); i++) {
		int offset = i * 4;
		models_indices.push_back(0 + offset);
		models_indices.push_back(1 + offset);
		models_indices.push_back(2 + offset);
		models_indices.push_back(2 + offset);
		models_indices.push_back(3 + offset);
		models_indices.push_back(0 + offset);
		std::cout << "Indices added" << std::endl;
	}

	modelsVA.Bind();
	modelsVB.Create(models_vertices.data(), models_vertices.size());
	modelsLayout.Push<float>(2);
	modelsVA.AddBuffer(modelsVB, modelsLayout);
	modelsIB.Create(models_indices.data(), models_indices.size());
}

void Scene::UpdateObjects() {
	for (int i = 0; i < m_models.size(); i++) {
		m_models[i].Update();
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

void Scene::RenderAll() {
		
}

void Scene::RenderTerrain() {

}