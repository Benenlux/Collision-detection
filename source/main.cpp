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

	Shader shader;

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
	unsigned int vertexShader = shader.CreateVertexShader(RESOURCE_DIR "/vertexShader.glsl");
	unsigned int fragmentShader = shader.CreateFragShader(RESOURCE_DIR "/fragmentShader.glsl");


	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//------- Object creation -------//
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

	VertexArray va;
	va.Bind();

	VertexBuffer vb(vertices.data(), vertices.size());
	vb.Bind();

	VertexBufferLayout layout;
	layout.Push<float>(3);
	va.AddBuffer(vb, layout);

	IndexBuffer ib(indices.data(), indices.size()); 
	ib.Bind(); 

	glm::vec3 offset = glm::vec3(0.0f, 0.0f, 0.0f);
	


	float bottom = -1.0f;
	
	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();

		//object.getPosition();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();

		{
			
			ImGui::Begin("Hello, world!");
			ImGui::Text("Mouse \n x: %.3f	y: %.3f", -1.0+io.MousePos.x/(io.DisplaySize.x/2), 1.0 - io.MousePos.y / (io.DisplaySize.y / 2));
			//ImGui::Text("Object \n x: %.3f	y: %.3f", object.position.x, object.position.y);
			ImGui::Text("Time elapsed: %.2f", glfwGetTime());
			ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			
			ImGui::End();

		}
		
		Input(window);

		


		ImGui::Render();

		
		glViewport(0, 0, io.DisplaySize.x, io.DisplaySize.y);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);

		va.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		glfwSwapBuffers(window);
		
	}
	Main::Exit();
}

void Main::Input(GLFWwindow* window) {
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