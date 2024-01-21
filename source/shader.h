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

class Object {
	//note to self: Object will have it's own buffers.
	//note to self: How the fuck am I going to draw 2 objects with different behavior
public:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	glm::vec3 position;
	Object(std::vector<float> vertices);

};