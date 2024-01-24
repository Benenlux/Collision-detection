#include "main.h"

int main() {
	Main main;
	main.Init();
}

int Main::Init() {
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);

	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "OpenGL", NULL, NULL);

	const char* glsl_version = "#version 130";

	glfwMakeContextCurrent(window);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//------- ImGui setup -------//
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	io.DisplaySize.x = window_width;
	io.DisplaySize.y = window_height;

	ImGui_ImplGlfw_InitForOpenGL(window, true);      
	ImGui_ImplOpenGL3_Init(glsl_version);	

	//------- Shader creation -------//
	Shader shader;

	shader.Create(RESOURCE_DIR "/VertexShader.glsl", RESOURCE_DIR "/FragmentShader.glsl");

	//------- Object creation -------//
	

	//------- Cube -------//
	std::vector<float> vertices = {
	// x	  y	   z
	 0.1f,  0.1f, 0.0f,  // top right
	 0.1f, -0.1f, 0.0f,  // bottom right
	-0.1f, -0.1f, 0.0f,  // bottom left
	-0.1f,  0.1f, 0.0f   // top left 
	};

	std::vector<unsigned int> indices = {
		0, 1, 3,
		1, 2, 3
	};

	//------- Triangle -------//
	std::vector<float> vertices2 = {
		-1.0f, -1.0f, 0.0f, // bottom left
		-1.0f, 0.0f, 0.0f, // top left
		0.0f, -1.0f, 0.0f, // bottom right
	};

	std::vector<unsigned int> indices2 = {
		0, 1, 2
	};


	VertexBufferLayout cubeLayout;

	Model Cube(vertices, indices, shader, cubeLayout, 3);
	
	VertexBufferLayout triangleLayout;
	Model Triangle(vertices2, indices2, shader, triangleLayout, 3);	

	float bottom = -1.0f;
	
	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();

		{
			
			ImGui::Begin("Hello, world!");
			ImGui::Text("Mouse \n x: %.3f	y: %.3f", -1.0+io.MousePos.x/(io.DisplaySize.x/2), 1.0 - io.MousePos.y / (io.DisplaySize.y / 2));
			ImGui::Text("x: %0.3f   y: %0.3f", Cube.m_translation.x, Cube.m_translation.y);
			ImGui::SliderFloat("scale", &Cube.scale, 0.1f, 2.0f);
			ImGui::Text("Time elapsed: %.2f", glfwGetTime());
			ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::Checkbox("Gravity", &Cube.rb.properties.gravityEnabled);
			ImGui::End();

		}
		
		Input(window, io);

		ImGui::Render();

		
		glViewport(0, 0, io.DisplaySize.x, io.DisplaySize.y);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader.m_shaderProgram);

		Cube.Render();
		Triangle.Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		glfwSwapBuffers(window);
		
	}
	Main::Exit();
}

void Main::Input(GLFWwindow* window, ImGuiIO& io) {
	if (ImGui::IsKeyPressed(ImGuiKey_Escape)) {
		glfwSetWindowShouldClose(window, true);
	}
}

int Main::Exit() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}