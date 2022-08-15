#pragma once
#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include"glm/glm.hpp"

std::string get_file_contents(const char* filename);

class Shader
{
public:
	// Reference ID of the Shader Program
	GLuint ID;
	// Constructor that build the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);
	// Activates the Shader Program
	void Activate();
	// Deletes the Shader Program
	void Delete();

	void SetUniformMat4f(const std::string& name, const glm::mat4& proj);
};