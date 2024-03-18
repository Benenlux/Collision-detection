#include "main.h"

int main() {
	Main main;
	main.Init();
}

int Main::Init() {

	//------- GLFW setup -------//
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE); 
	GLFWwindow* window = glfwCreateWindow(900, 700, "OpenGL", NULL, NULL);

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

	const char* glsl_version = "#version 130";

	ImGui_ImplGlfw_InitForOpenGL(window, true);      
	ImGui_ImplOpenGL3_Init(glsl_version);	

	float ratio = io.DisplaySize.x / io.DisplaySize.y;
	
	Scene scene(&ratio, &io.DeltaTime);

	//------- Main loop -------//
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		ratio = io.DisplaySize.x / io.DisplaySize.y;

		ImGuiRender(window, io, &scene, ratio);

		ImGui::Render();

		glViewport(0, 0, io.DisplaySize.x, io.DisplaySize.y);
		
		glClearColor(background_color.x, background_color.y, background_color.z, background_color.w);
		glClear(GL_COLOR_BUFFER_BIT);

		scene.shader.BindUniform1f("ratio", ratio);
		scene.Render(ratio, io.DeltaTime);
		

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		glfwSwapBuffers(window);
		
	}
	
	Main::Exit();
}

void Main::ImGuiRender(GLFWwindow* window, ImGuiIO& io, Scene* scene, float ratio) {
	
	ImGui::NewFrame();

	ImGui::Begin("Handy info", 0, ImGuiWindowFlags_NoNavFocus );
	ImGui::Text("Click on the screen to add a circle");
	ImGui::Text("FPS: %.1f", 1 / io.DeltaTime);
	ImGui::Text("Models: %d", scene->scene_objects.size());
	

	if (scene->is_paused) {
		if (ImGui::Button("Resume")) {
			scene->Play();
		}
	}
	else {
		if (ImGui::Button("Pause")) {
			scene->Pause();
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("Reset")) {
		scene->Reset();
	}

	ImGui::SliderFloat("Radius", &model_radius, 0.001f, 0.5f);
	ImGui::SliderInt("Segments", &model_segments, 8, 100);
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
	{
		ImGui::SetTooltip("Determines how smooth the circle is. WARNING: A high number of segments can impact performance");
	}
	ImGui::ColorEdit3("Background color", (float*)&background_color);
	ImGui::ColorEdit3("Model color", (float*)&model_colors);

	ImGui::End();
	
	if (ImGui::IsKeyPressed(ImGuiKey_Escape)) {
		glfwSetWindowShouldClose(window, true);
	}
	if (ImGui::IsKeyPressed(ImGuiKey_Space)) {
		if (scene->is_paused) {
			scene->Play();
		}
		else {
			scene->Pause();
		}
	}

	if (!io.WantCaptureMouse) {
		if (ImGui::IsMouseClicked(0)) {
			double x, y;

			glfwGetCursorPos(window, &x, &y);

			//Normalize the mouse coordinates to the screen space
			x = (x - (io.DisplaySize.x / 2)) * ratio / (io.DisplaySize.x / 2);
			y = (y - (io.DisplaySize.y / 2)) / (io.DisplaySize.y / 2);

			scene->AddCircle(model_radius, x, -y, model_segments, glm::vec3(model_colors.x, model_colors.y, model_colors.z));
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