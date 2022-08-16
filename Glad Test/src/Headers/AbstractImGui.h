#pragma once
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"


class ImGuiInterface
{
public:
	ImGuiInterface(GLFWwindow* window);
	~ImGuiInterface();
	void ImGuiRender();
	void ImGuiNewFrame();


private:
	const char* glsl_version = "#version 330";

};
