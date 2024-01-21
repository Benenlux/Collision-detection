#include "shader.h"

unsigned int Shader::CreateVertexShader(const std::string& path) {
	std::string shader = Load_Shader(path);
	const char* shaderSource = shader.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &shaderSource, NULL);
	glCompileShader(vertexShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return vertexShader;
}

unsigned int Shader::CreateFragShader(const std::string& path) {
	std::string shader = Load_Shader(path);
	const char* shaderSource = shader.c_str();

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &shaderSource, NULL);
	glCompileShader(fragmentShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAG::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return fragmentShader;
}

void Shader::BindUniform4f(unsigned int shaderProgram, std::string uniformName, glm::vec4 data) {
	int vertexColorLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());
	glUniform4f(vertexColorLocation, data.x, data.y, data.z, data.w);
}

std::string Shader::Load_Shader(const std::string& path) {
	std::ifstream file(path);
	std::string line;
	std::string shader;

	while (getline(file, line)) {
		shader += line + "\n";
	}

	return shader;
}