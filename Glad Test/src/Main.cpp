#include "Headers/MyOpenGLRenderer.h"
#include "ArraySorting.h"


int main()
{
	

	/* INITIALIZATION */

	// Starter class used to hide OpenGL boilerplate and decrease ammount of code in Main.cpp
	// Default size is changable
	Starter starter("MyWindow");
	Shader shader("C:/Users/Karol/source/repos/Glad Test/Glad Test/src/Shaders/default.vert", "C:/Users/Karol/source/repos/Glad Test/Glad Test/src/Shaders/default.frag");
	ImGuiInterface GuiInterface(starter.window);
	Renderer renderer(&shader);



	/* APPLICATION SPECIFIC CODE */
	// (maybe move some of the initialization stuff here as someone might want to specifi shaders, GUI, etc.)
	ArraySorting sorter(40);
	sorter.CreateVertices();
	sorter.CreateIndicies();

	// MOVE IT TO ANOTHER FILE
	// Here layout will be three floats X,Y,Z and another thre for colors R,G,B
	VertexBufferLayout layout;
	// Cordinates
	layout.Push<float>(3);
	// Color
	layout.Push<float>(3);

	renderer.SetVBLayout(layout);

	int* list = (int*)sorter.getIndicies();

	renderer.SetVertexBuffer( sorter.getVBsize(), sorter.getVertices());
	renderer.SetIndexBuffer(  sorter.getIBsize(), sorter.getIndicies());

	// Coordinates for moving the scene
	static float x_cord = 0.0f;
	static float y_cord = 0.0f;

	/* MAIN WINDOW LOOP */
	while (!glfwWindowShouldClose(starter.window))
	{
		starter.window_maximize_callback();
		renderer.Clear();
		GuiInterface.ImGuiNewFrame();
		
		if (true)

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{
			ImGui::Begin("Control Panel");                          // Create a window and append into it.
			// Scene movement
			ImGui::SliderFloat("DistanceX", &x_cord, 0.f, 10000.f);      
			ImGui::SliderFloat("DistanceY", &y_cord, 0.f, 10000.f);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);	// Application benchmark
			ImGui::End();	// Terminate ImGui
		}

		starter.view = glm::translate(glm::mat4(1.0f), glm::vec3(x_cord, y_cord, 0));
		starter.MVP = starter.proj * starter.view;
		shader.SetUniformMat4f("u_MVP", starter.MVP);
		
		

		renderer.Draw(sorter.getIBsize()*4);
		GuiInterface.ImGuiRender();
		
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(starter.window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	
	

	

	return 0;
}