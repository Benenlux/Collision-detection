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
	Scene scene;

	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		ImGuiRender(window, io, &scene);

		ImGui::Render();
		
		

		glViewport(0, 0, io.DisplaySize.x, io.DisplaySize.y);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		scene.StressTest(1 / io.DeltaTime);
		scene.RenderAll(io.DeltaTime*time_scale);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		
		glfwSwapBuffers(window);
		
	}
	Main::Exit();
}

void Main::ImGuiRender(GLFWwindow* window, ImGuiIO& io, Scene* scene) {
	
	ImGui::NewFrame();

	ImGui::Begin("Hello, world!", 0, ImGuiWindowFlags_NoNavFocus );
	ImGui::Text("Mouse \n x: %.3f	y: %.3f", -1.0 + io.MousePos.x / (io.DisplaySize.x / 2), 1.0 - io.MousePos.y / (io.DisplaySize.y / 2));
	ImGui::Text("FPS: %.1f", 1 / io.DeltaTime);
	ImGui::Text("Models: %d", scene->m_models.size());
	if (scene->isPaused) {
		if (ImGui::Button("Resume")) {
			scene->Play();
		}
	}
	else {
		if (ImGui::Button("Pause")) {
			scene->Pause();
		}
	}
	ImGui::SliderFloat("Width", &model_width, 0.1f, 0.5f);
	ImGui::SliderFloat("Height", &model_height, 0.01f, 0.5f);
	ImGui::SliderFloat("Time Scale", &time_scale, 0.1f, 2.0f);
	ImGui::End();
	

	if (ImGui::IsKeyPressed(ImGuiKey_Escape)) {
		glfwSetWindowShouldClose(window, true);
	}
	if (!io.WantCaptureMouse) {
		if (ImGui::IsMouseClicked(0)) {
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			x = (x - (io.DisplaySize.x / 2)) / (io.DisplaySize.x / 2);
			y = (y - (io.DisplaySize.y / 2)) / (io.DisplaySize.y / 2);
			scene->AddModel(model_height, model_width, x, -y);
		}
	}
	
	if (ImGui::IsKeyPressed(ImGuiKey_Space)) {
		if (scene->isPaused) {
			scene->Play();
		}
		else {
			scene->Pause();
		}
	}
}

int Main::Exit() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}