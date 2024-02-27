#pragma once

//Standard libraries
#include <iostream>
#include <fstream>
#include <string>

//Graphics libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//Math libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Custom libraries
#include "Scene.h"


class Main {
public:
	int Main::Init();

private:
	int window_height = 900;
	int window_width = window_height * 1.78;
	

	float model_width = 0.1f;
	float model_height = 0.1f;
	float model_radius = 0.1f;
	int model_segments = 16;

	enum class SpawnType {
		Square,
		Circle,
	};

	SpawnType spawn_type = SpawnType::Square;

	float time_scale = 1.0f;
	
	void Main::ImGuiRender(GLFWwindow* window, ImGuiIO& io, Scene* scene, float ratio);
	int Main::Exit();
	
};