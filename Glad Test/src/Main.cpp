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
	
	
	ArraySorting sorter(100, starter.window);
	renderer.SetVBLayout(sorter.getLayout());
	renderer.SetVertexBuffer( sorter.getVBsize(), sorter.getVertices());
	renderer.SetIndexBuffer(  sorter.getIBsize(), sorter.getIndicies());


	/* MAIN WINDOW LOOP */
	while (!glfwWindowShouldClose(starter.window))
	{
		starter.window_maximize_callback();		// Adjust contex when window is maximized
		renderer.Clear();
		GuiInterface.ImGuiNewFrame();
		
		if (true)

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{
			ImGui::Begin("Control Panel");                          // Create a window and append into it.
			if (ImGui::Button("Sort!")) {
				sorter.BubbleSort(&renderer);
			}
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);	// Application benchmark
			ImGui::End();	// Terminate ImGui
		}


	
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