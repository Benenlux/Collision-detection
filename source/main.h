#pragma once

//Standard libraries
#include <iostream>
#include <string>

//Graphics libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//Math libraries
#include <glm/glm.hpp>

//Custom libraries
#include "Scene.h"


class Main {
public:
	int Main::Init();

private:
	int window_width = 900;
	int window_height = 700;
	
	float model_radius = 0.1f;
	int model_segments = 16;

	ImVec4 model_colors = ImVec4(1.0f, 0.5f, 0.2f, 1.0f);
	ImVec4 background_color = ImVec4(0.2f, 0.3f, 0.3f, 1.0f);

	
	void Main::ImGuiRender(GLFWwindow* window, ImGuiIO& io, Scene* scene, float ratio);
	int Main::Exit();
	
};