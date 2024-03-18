#include "Scene.h"

Scene::Scene(float* ratio, float* deltaTime) : m_ratio(ratio), m_delta_time(deltaTime) {
	shader.Create(RESOURCE_DIR "/VertexShader.glsl", RESOURCE_DIR "/FragmentShader.glsl");
	scene_shader = shader.m_shaderProgram;

	glGenVertexArrays(1, &objectsVA);

	glBindVertexArray(objectsVA);

	objectsVB.Create(objects_vertices.data(), objects_vertices.size());

	//Vertex Array for the position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

	//Vertex Array for the color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	
	objectsIB.Create(objects_indices.data(), objects_indices.size());
}

Scene::~Scene() {
	objectsIB.Delete();
	objectsVB.Delete();
	glDeleteVertexArrays(1, &objectsVA);
}

void Scene::AddCircle(float radius, float x_coord, float y_coord, int segments, glm::vec3 color) {
	
	Object object;
	object.CreateCircle(radius, x_coord, y_coord, segments, color);

	scene_objects.push_back(object);

	for (int i = 0; i < object.m_vertices.size(); i += 1) {
		objects_vertices.push_back(object.m_vertices[i]);

		//Add the color to each vertex
		objects_vertices.push_back(object.m_color.x);
		objects_vertices.push_back(object.m_color.y);
		objects_vertices.push_back(object.m_color.z);
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

	//Resive the buffer to fit the added vertices
	objectsVB.UpdateSize(objects_vertices.data(), objects_vertices.size());
	objectsIB.UpdateSize(objects_indices.data(), objects_indices.size());
}

void Scene::Render(float ratio, float deltaTime) {

	RenderObjects();
	glUseProgram(scene_shader);
	glBindVertexArray(objectsVA);
	glDrawElements(GL_TRIANGLES, objects_indices.size(), GL_UNSIGNED_INT, nullptr);
}



void Scene::RenderObjects() {
	int vertex_count = 0;

	//Go through all the objects in the vector
	for (int i = 0; i < scene_objects.size(); i++) {
		if (!is_paused) {
			UpdateObject(&scene_objects[i], i);
		}
		
		//Go through all the vertices in the object
		for (int j = 0; j < scene_objects[i].m_vertices.size(); j += 2) {

			//Apply the translations in world space to the vertices of the object
			objects_vertices[vertex_count] = scene_objects[i].m_vertices[j] + scene_objects[i].position.x;
			objects_vertices[vertex_count + 1] = scene_objects[i].m_vertices[j + 1] + scene_objects[i].position.y;

			objects_vertices[vertex_count + 2] = scene_objects[i].m_color.x;
			objects_vertices[vertex_count + 3] = scene_objects[i].m_color.y;
			objects_vertices[vertex_count + 4] = scene_objects[i].m_color.z;

			vertex_count += 5;
		}
	}

	//Bind the updated vertices to the buffer
	objectsVB.Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, objects_vertices.size() * sizeof(GLfloat), objects_vertices.data());
}

void Scene::UpdateObject(Object* object, int object_number) {
	if (object->is_on_ground == false) {
		object->Translate(0.0f, -0.5f * *m_delta_time);
	}

	CheckIfGrounded(object);
	CheckIfOnEnd(object, *m_ratio);

	//If there are objects to collide with, check for collision
	if (scene_objects.size() > 1) {

		//Go through all the other objects in the scene
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

void Scene::Reset() {
	scene_objects.clear();
	objects_vertices.clear();
	objects_indices.clear();
	index_offset = 0;
}

