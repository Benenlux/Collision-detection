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

void Scene::Init() {
	objectsVA.Bind();
	objectsVB.Create(objects_vertices.data(), objects_vertices.size());
	objects_layout.Push<float>(2);
	objectsVA.AddBuffer(objectsVB, objects_layout);
	objectsIB.Create(objects_indices.data(), objects_indices.size());
}

void Scene::AddCircle(float radius, float x_coord, float y_coord, int segments) {
	Object object;
	object.CreateCircle(radius, x_coord, y_coord, segments);
	objects.push_back(object);
	for (int i = 0; i < object.m_vertices.size(); i++) {
		objects_vertices.push_back(object.m_vertices[i]);
	}

	for (int i = 0; i < segments; i++) {
		objects_indices.push_back(0 + index_offset);
		objects_indices.push_back(i + 1 + index_offset);
		if (i == segments - 1) {
			objects_indices.push_back(1 + index_offset);
		}
		else {
			objects_indices.push_back(i + 2 + index_offset);
		}
	}
	index_offset += segments + 1;

	//Update the buffer with the new size and data
	objectsVB.Update(objects_vertices.data(), objects_vertices.size());
	objectsIB.Update(objects_indices.data(), objects_indices.size());
}

void Scene::Render(float time) {
	deltaTime = time;
	if (!isPaused) {
		UpdateObjects();
	}
	RenderObjects();
	glUseProgram(sceneShader);
	objectsVA.Bind();
	glDrawElements(GL_TRIANGLES, objects_indices.size(), GL_UNSIGNED_INT, nullptr);
}



void Scene::RenderObjects() {
	objects_vertices.clear();
	//Go through all the objects in the vector
	for (int i = 0; i < objects.size(); i++) {
		//Go through all the vertices in the object
		for (int j = 0; j < objects[i].m_vertices.size(); j += 2) {
			//Apply the translations in world space to the vertices of the object
			objects_vertices.push_back(objects[i].m_vertices[j] + objects[i].position.x);
			objects_vertices.push_back(objects[i].m_vertices[j+1] + objects[i].position.y);
		}
	}
	objectsVB.Bind();
	//Bind the new vertices to the buffer
	glBufferSubData(GL_ARRAY_BUFFER, 0, objects_vertices.size() * sizeof(GLfloat), objects_vertices.data());
}

void Scene::UpdateObjects() {
	//Go through all the objects in the vector
	for (int i = 0; i < objects.size(); i++) {
		//Check for collisions if there's more than one object
		if (objects[i].isOnGround == false) {
			objects[i].Translate(0.0f, -0.5f*deltaTime);
			CheckIfGrounded(&objects[i]);
		}
		
		if (objects.size() > 1) {
			//Go through all the objects in the vector
			for (int j = 0; j < objects.size(); j++) {
				//If the object is not the same as the one we are checking, check for collision
				if (i != j) {
					CheckCollision(&objects[i], &objects[j]);
				}
			}
		}
	}
}

void Scene::Pause(){
	isPaused = true;
}

void Scene::Play(){
	isPaused = false;
}

