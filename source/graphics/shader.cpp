#include "shader.h"

void Shader::Create(const std::string& vertexPath, const std::string& fragmentPath) {
	m_vertexShader = CreateVertexShader(vertexPath);
	std::cout << fragmentPath;
	m_fragmentShader = CreateFragShader(fragmentPath);
	m_shaderProgram = glCreateProgram();

	glAttachShader(m_shaderProgram, m_vertexShader);
	glAttachShader(m_shaderProgram, m_fragmentShader);

	glLinkProgram(m_shaderProgram);
	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);
}

void Shader::AttachFragment() {
	glAttachShader(m_shaderProgram, m_fragmentShader);
}

void Shader::AttachVertex() {
	glAttachShader(m_shaderProgram, m_vertexShader);
}

void Shader::LinkProgram() {
	glLinkProgram(m_shaderProgram);
	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);
}

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

void Shader::BindUniform3f(std::string uniformName, glm::vec3 data) {
	int vertexColorLocation = glGetUniformLocation(m_shaderProgram, uniformName.c_str());
	glUniform3f(vertexColorLocation, data.x, data.y, data.z);
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