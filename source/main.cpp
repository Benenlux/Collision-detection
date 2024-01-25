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

	//------- Object creation -------//
	
	Shader shader;
	shader.Create(RESOURCE_DIR "/VertexShader.glsl", RESOURCE_DIR "/FragmentShader.glsl");
	std::vector<float> vertices = {
		-0.2f,  0.2f,  // top left
		-0.2f, -0.2f,  // bottom left
		 0.2f, -0.2f,  // bottom right
		 0.2f,  0.2f,  // top right 
		-0.8f,  0.2f,
		-0.8f, -0.2f,
		-0.4f, -0.2f,
		-0.4f,  0.2f
	};
	
	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4
	};
	VertexArray va;
	va.Bind();
	VertexBufferLayout layout;
	layout.Push<float>(2);
	
	VertexBuffer vb;
	vb.Create(&vertices, vertices.size() * sizeof(float));
	va.AddBuffer(vb, layout);
	IndexBuffer ib;
	ib.Create(indices.data(), indices.size());
	va.Bind();

	float bottom = -1.0f;
	
	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();

		{
			
			ImGui::Begin("Hello, world!");
			ImGui::Text("Mouse \n x: %.3f	y: %.3f", -1.0+io.MousePos.x/(io.DisplaySize.x/2), 1.0 - io.MousePos.y / (io.DisplaySize.y / 2));
			ImGui::End();

		}
		
		Input(window, io);

		ImGui::Render();

		
		glViewport(0, 0, io.DisplaySize.x, io.DisplaySize.y);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		

		glUseProgram(shader.m_shaderProgram);

		va.Bind();
		glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0);

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