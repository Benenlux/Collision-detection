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

	void Create(const std::string& vertexPath, const std::string& fragmentPath);
	
	void BindUniform3f(std::string uniformName, glm::vec3 data);
	void BindMat4(std::string uniformName, glm::mat4 data);
	void BindUniform2f(std::string uniformName, glm::vec2 data);
	void BindUniform1f(std::string uniformName, float data);
	void AttachFragment();
	void AttachVertex();
	void LinkProgram();
private:
	
	std::string  Load_Shader(const std::string& path);
	unsigned int CreateVertexShader(const std::string& path);
	unsigned int CreateFragShader(const std::string& path);
};

