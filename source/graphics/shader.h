#pragma once

//Standard libraries
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

//Graphics libraries
#include <glad/glad.h>

//Math libraries
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader {
public:
	unsigned int m_shaderProgram;
	unsigned int m_vertexShader;
	unsigned int m_fragmentShader;

	void Shader::Create(const std::string& vertexPath, const std::string& fragmentPath);
	
	void Shader::BindUniform3f(std::string uniformName, glm::vec3 data);
	void Shader::BindMat4(std::string uniformName, glm::mat4 data);
	void Shader::AttachFragment();
	void Shader::AttachVertex();
	void Shader::LinkProgram();
private:
	
	std::string Shader::Load_Shader(const std::string& path);
	unsigned int Shader::CreateVertexShader(const std::string& path);
	unsigned int Shader::CreateFragShader(const std::string& path);
};

