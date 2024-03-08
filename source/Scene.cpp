#include "Scene.h"

Scene::Scene() {

	shader.Create(RESOURCE_DIR "/VertexShader.glsl", RESOURCE_DIR "/FragmentShader.glsl");
	scene_shader = shader.m_shaderProgram;

	objectsVA.Bind();
	objectsVB.Create(objects_vertices.data(), objects_vertices.size());
	objects_layout.Push<float>(2);
	objectsVA.AddBuffer(objectsVB, objects_layout);
	objectsIB.Create(objects_indices.data(), objects_indices.size());
}

Scene::~Scene() {
	objectsIB.Delete();
	objectsVB.Delete();
	objectsVA.~VertexArray();	
}

void Scene::AddCircle(float radius, float x_coord, float y_coord, int segments) {
	Object object;
	object.CreateCircle(radius, x_coord, y_coord, segments);
	scene_objects.push_back(object);
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
	objectsVB.UpdateSize(objects_vertices.data(), objects_vertices.size());
	objectsIB.UpdateSize(objects_indices.data(), objects_indices.size());
}

void Scene::Render() {
	RenderObjects();
	glUseProgram(scene_shader);
	objectsVA.Bind();
	glDrawElements(GL_TRIANGLES, objects_indices.size(), GL_UNSIGNED_INT, nullptr);
}



void Scene::RenderObjects() {
	//Empty the vector so the updated vertices can be pushed back
	objects_vertices.clear();

	//Go through all the objects in the vector
	for (int i = 0; i < scene_objects.size(); i++) {
		UpdateObject(&scene_objects[i], i);

		//Go through all the vertices in the object
		for (int j = 0; j < scene_objects[i].m_vertices.size(); j += 2) {
			//Apply the translations in world space to the vertices of the object
			objects_vertices.push_back(scene_objects[i].m_vertices[j] + scene_objects[i].position.x);
			objects_vertices.push_back(scene_objects[i].m_vertices[j+1] + scene_objects[i].position.y);
		}
	}

	//Bind the updated vertices to the buffer
	objectsVB.Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, objects_vertices.size() * sizeof(GLfloat), objects_vertices.data());
}

void Scene::UpdateObject(Object* object, int object_number) {
	if (object->is_on_ground == false) {
		object->Translate(0.0f, -0.0005f);
		CheckIfGrounded(object);
	}

	//Constantly check if the object is on the end
	CheckIfOnEnd(object);

	//If there are objects to collide with, check for collision
	if (scene_objects.size() > 1) {

		//Go through all the objects in the vector
		for (int j = 0; j < scene_objects.size(); j++) {

			//If the object is not the same as the one it is checking, check for collision
			if (object_number != j) {
				CheckCollision(object, &scene_objects[j]);
			}
		}
	}
}


void Scene::Pause(){
	is_paused = true;
}

void Scene::Play(){
	is_paused = false;
}

