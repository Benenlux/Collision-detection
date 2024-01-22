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
#include "shader.h"
#include "object.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"


class Main {
public:
	int Main::Init();

private:
	int window_width = 800;
	int window_height = 600;
	
	void Main::Input(GLFWwindow* window);
	int Main::Exit();
	
};