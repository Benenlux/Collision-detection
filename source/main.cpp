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

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); 
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

	
	Scene scene;

	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		float ratio = io.DisplaySize.x / io.DisplaySize.y;

		ImGuiRender(window, io, &scene, ratio);

		ImGui::Render();

		glViewport(0, 0, window_width, window_height);
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		

		scene.Render(io.DeltaTime*time_scale);
		scene.shader.BindUniform1f("ratio", ratio);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		glfwSwapBuffers(window);
		
	}
	
	Main::Exit();
}

void Main::ImGuiRender(GLFWwindow* window, ImGuiIO& io, Scene* scene, float ratio) {
	
	ImGui::NewFrame();

	ImGui::Begin("Hello, world!", 0, ImGuiWindowFlags_NoNavFocus );
	ImGui::Text("Mouse \n x: %.3f	y: %.3f", -1.0 + (io.MousePos.x / (window_width / 2)), 1.0 - io.MousePos.y / (io.DisplaySize.y / 2));
	ImGui::Text("FPS: %.1f", 1 / io.DeltaTime);
	ImGui::Text("Models: %d", scene->objects.size());
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

	if (spawn_type == SpawnType::Circle) {
		if (ImGui::Button("Cirlce")) {
			spawn_type = SpawnType::Square;
		}
	}
	else if (spawn_type == SpawnType::Square) {
		if (ImGui::Button("Square")) {
			spawn_type = SpawnType::Circle;
		}
	}

	if (spawn_type == SpawnType::Square) {
		ImGui::SliderFloat("Width", &model_width, 0.001f, 0.5f);
		ImGui::SliderFloat("Height", &model_height, 0.001f, 0.5f);
	}
	else if (spawn_type == SpawnType::Circle) {
		ImGui::SliderFloat("Radius", &model_radius, 0.001f, 0.5f);
		ImGui::SliderInt("Segments", &model_segments, 8, 100);
	}
	
	ImGui::SliderFloat("Time Scale", &time_scale, 0.1f, 2.0f);
	ImGui::End();
	

	if (ImGui::IsKeyPressed(ImGuiKey_Escape)) {
		glfwSetWindowShouldClose(window, true);
	}
	if (!io.WantCaptureMouse) {
		if (ImGui::IsMouseClicked(0)) {
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			x = (x - (io.DisplaySize.x / 2)) / (io.DisplaySize.x/ 2);
			y = (y - (io.DisplaySize.y / 2)) / (io.DisplaySize.y / 2);
			if (spawn_type == SpawnType::Circle)
				scene->AddCircle(model_radius, x*ratio, -y, model_segments);
			else if (spawn_type == SpawnType::Square) {
				scene->AddSquare(model_height, model_width, x*ratio, -y);
			}
			
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