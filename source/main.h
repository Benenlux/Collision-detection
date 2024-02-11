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
	int window_width = 800;
	int window_height = 600;

	float model_width = 0.1f;
	float model_height = 0.1f;

	float time_scale = 1.0f;
	
	void Main::ImGuiRender(GLFWwindow* window, ImGuiIO& io, Scene* scene);
	int Main::Exit();
	
};