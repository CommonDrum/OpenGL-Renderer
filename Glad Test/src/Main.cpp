#include "Headers/Header.h"
#include "Headers/Renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"



// Vertices coordinates
GLfloat vertices[] =
{ //               COORDINATES                  /     COLORS           //
	-0.5f, -0.5f, 0.0f,     0.8f, 0.37f,  0.72f, // Lower left corner
	 0.5f, -0.5f, 0.0f,     0.8f, 0.34f,  0.52f, // Lower right corner
	 0.0f,  0.5f, 0.0f,     0.0f, 0.6f,  0.32f, // Upper corner
	-0.25f, 0.5f, 0.0f,     0.9f, 0.75f, 0.17f, // Inner left
	 0.25f, 0.5f, 0.0f,     0.9f, 0.75f, 0.17f, // Inner right
	 0.0f, -0.5f, 0.0f,     0.8f, 0.3f,  0.02f  // Inner down
};

// Indices for vertices order
GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
};



int main()
{
	// Create matrix to project objects to 2D screen
	glm::mat4 proj = glm::ortho(-2.0f, 2.0f, 1.5f, 1.5f, -1.0f, 1.0f);


	// Starter class used to hide OpenGL boilerplate and decrease ammount of code in Main.cpp
	Starter starter(800,800,"MyWindow");

	//Load and activate shaders
	Shader shaderObject("C:/Users/Karol/source/repos/Glad Test/Glad Test/src/Shaders/default.vert", "C:/Users/Karol/source/repos/Glad Test/Glad Test/src/Shaders/default.frag");
	shaderObject.Activate();
	//shaderObject.SetUniformMat4f("u_MVP", proj);

	// Generates Vertex Array Object and binds it
	VertexArray VA;
	VA.Bind();

	// Generate Vertex and Element Buffer Objects and link them to vertices
	VertexBuffer  VBO1(vertices, sizeof(vertices));
	IndexBuffer EBO1(indices,  sizeof(indices));


	VertexBufferLayout layout;
	// Cordinates
	layout.Push<float>(3);
	// Color
	layout.Push<float>(3);

	VA.LinkVertexBuffer(VBO1, layout);

	Renderer renderer;
	

	// Main while loop
	while (!glfwWindowShouldClose(starter.window))
	{
		
		renderer.Clear();
		VA.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(starter.window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Cleanup
	VA.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderObject.Delete();
	return 0;
}