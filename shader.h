#pragma once

//Standard libraries
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

//Graphics libraries
#include <glad/glad.h>

class Shader {
public:
	std::vector<float> vertices = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	unsigned int Shader::CreateVertexShader(const std::string& path);
	unsigned int Shader::CreateFragShader(const std::string& path);

private:
	
	std::string Shader::Load_Shader(const std::string& path);
	
};