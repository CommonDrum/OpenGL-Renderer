#include "Headers/MyOpenGLRenderer.h"
#include "ArraySorting.h"




//Abstract MVP

//

// Vertices coordinates
GLfloat vertices[] =
{ //   COORDINATES    \\    \\     COLORS     //
	 0.0f,  10.0f, 0.0f,     0.8f, 0.37f,  0.72f, 
	 10.0f, -10.0f, 0.0f,     0.8f, 0.34f,  0.52f, 
	-10.0f,  -10.0f, 0.0f,     0.0f, 0.6f,  0.32f
	
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2 
};




int main()
{
	// Create matrix to project objects to 2D screen
	glm::mat4 proj = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 MVP = proj * view;


	// Starter class used to hide OpenGL boilerplate and decrease ammount of code in Main.cpp
	Starter starter(800, 800, "MyWindow");
	glfwSwapInterval(1); // Enable vsync

	Shader shader("C:/Users/Karol/source/repos/Glad Test/Glad Test/src/Shaders/default.vert", "C:/Users/Karol/source/repos/Glad Test/Glad Test/src/Shaders/default.frag");
	
	ArraySorting sorter(20);

	sorter.CreateVertices();
	sorter.CreateIndicies();

	


	

	Renderer renderer(&shader);
	ImGuiInterface GuiInterface(starter.window);

	// MOVE IT TO ANOTHER FILE
	// Here layout will be three floats X,Y,Z and another thre for colors R,G,B
	VertexBufferLayout layout;
	// Cordinates
	layout.Push<float>(3);
	// Color
	layout.Push<float>(3);

	renderer.SetVBLayout(layout);

	int* list = (int*)sorter.getIndicies();

	for (int i = 0; i < sorter.getIBsize(); i++)
	{
		std::cout << list[i] << std::endl;
	}
	
		static int x_cord = 0.0f;

		renderer.SetVertexBuffer( sorter.getVBsize(), sorter.getVertices());
		renderer.SetIndexBuffer(  sorter.getIBsize(), sorter.getIndicies());


	// Main while loop
	while (!glfwWindowShouldClose(starter.window))
	{
		renderer.Clear();
		GuiInterface.ImGuiNewFrame();
		
		if (true)

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{
			ImGui::Begin("Control Panel");                          // Create a window called "Hello, world!" and append into it.
			ImGui::SliderInt("Distance", &x_cord, -100, 100);       // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		view = glm::translate(glm::mat4(1.0f), glm::vec3(x_cord, 0, 0));
		MVP = proj * view;
		shader.SetUniformMat4f("u_MVP", MVP);
		

		renderer.Draw(sorter.getIBsize()*4);
		GuiInterface.ImGuiRender();
		
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(starter.window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	
	

	

	return 0;
}