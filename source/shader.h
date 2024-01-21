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

class Shader {
public:
	
	unsigned int Shader::CreateVertexShader(const std::string& path);
	unsigned int Shader::CreateFragShader(const std::string& path);
	void Shader::BindUniform4f(unsigned int shaderProgram, std::string uniformName, glm::vec4 data);

private:
	
	std::string Shader::Load_Shader(const std::string& path);
	
};

