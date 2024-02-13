#include "Scene.h"

Scene::Scene() {
	shader.Create(RESOURCE_DIR "/VertexShader.glsl", RESOURCE_DIR "/FragmentShader.glsl");
	sceneShader = shader.m_shaderProgram;
	Init();
}

Scene::~Scene() {
	objectsIB.Delete();
	objectsVB.Delete();
	objectsVA.~VertexArray();
	
	
}

void Scene::AddObject(float height, float width, float x_coord, float y_coord) {
	auto object = std::shared_ptr<Object>(new Object(height, width, x_coord, y_coord));
	objects.push_back(object);
	for (int i = 0; i < object->m_vertices.size(); i++) {
		objects_vertices.push_back(object->m_vertices[i]);
	}
	
	
	int offset = (objects.size() - 1) * 4;
	objects_indices.push_back(0 + offset);
	objects_indices.push_back(1 + offset);
	objects_indices.push_back(2 + offset);
	objects_indices.push_back(2 + offset);
	objects_indices.push_back(3 + offset);
	objects_indices.push_back(0 + offset);
	std::cout << offset << std::endl;
	
	objectsVB.Update(objects_vertices.data(), objects_vertices.size());
	objectsIB.Update(objects_indices.data(), objects_indices.size());
}

void Scene::RenderObjects() {
	if (!isPaused) {
		UpdateObjects();
	}

	objectsVA.Bind();
	glDrawElements(GL_TRIANGLES, objects_indices.size(), GL_UNSIGNED_INT, nullptr);
}

void Scene::Init() {	
	objectsVA.Bind();
	objectsVB.Create(objects_vertices.data(), objects_vertices.size());
	objects_layout.Push<float>(2);
	objectsVA.AddBuffer(objectsVB, objects_layout);
	objectsIB.Create(objects_indices.data(), objects_indices.size());
}

void Scene::UpdateObjects() {
	CheckCollisions();
	for (int i = 0; i < objects.size(); i++) {
		//objects[i]->Update(deltaTime);
	}
	objects_vertices.clear();
	for (int i = 0; i < objects.size(); i++) {
		for (int j = 0; j < objects[i]->m_vertices.size(); j++) {
			objects_vertices.push_back(objects[i]->m_vertices[j]);
		}
	}
	objectsVB.Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, objects_vertices.size() * sizeof(GLfloat), objects_vertices.data());
}

void Scene::Pause(){
	isPaused = true;
}

void Scene::Play(){
	isPaused = false;
}

void Scene::RenderAll(float time){
	deltaTime = time;
	glUseProgram(sceneShader);
	RenderObjects();
}
void Scene::CheckCollisions() {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->bottom_right.y < -1.0f) {
			float difference = objects[i]->bottom_right.y - -1.0f;
			objects[i]->Transform(glm::vec2(0.0f, -difference));
		}
	}
}

void Scene::StressTest(float fps) {
	if (fps > 200) {
		AddObject(0.1f, 0.1f, 0.0f, 0.0f);
	}
}

void Scene::AddCircle(float radius, float x_coord, float y_coord) {
	Object testObject;
	testObject.CreateCircle(radius, x_coord, y_coord);
	objects.push_back(std::make_shared<Object>(testObject));
	for (int i = 0; i < testObject.m_vertices.size(); i++) {
		objects_vertices.push_back(testObject.m_vertices[i]);
	}
	
	for (int i = 0; i < 8; i++) {
		int offset = (objects.size() - 1) * 9;
		objects_indices.push_back(0+offset);
		objects_indices.push_back(i+1+offset);
		if (i == 7) {
			objects_indices.push_back(1+offset);
		}
		else {
			objects_indices.push_back(i + 2+offset);
		}
	}
	

	objectsVB.Update(objects_vertices.data(), objects_vertices.size());
	objectsIB.Update(objects_indices.data(), objects_indices.size());
}