#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h> 
#include <iostream>
#include "ShaderClass.h"

class Starter
{
public:
	Starter(int sizeX, int sizeY, std::string name);
	~Starter();
	GLFWwindow* window;

};
