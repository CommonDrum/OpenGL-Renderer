#include "Headers/Header.h"





//TODO: 
//Change getsize to get count 


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
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(50, 0, 0));

	glm::mat4 MVP = proj * view;

	// Starter class used to hide OpenGL boilerplate and decrease ammount of code in Main.cpp
	Starter starter(800, 800, "MyWindow");
	glfwSwapInterval(1); // Enable vsync

	//Load and activate shaders
	Shader shader("C:/Users/Karol/source/repos/Glad Test/Glad Test/src/Shaders/default.vert", "C:/Users/Karol/source/repos/Glad Test/Glad Test/src/Shaders/default.frag");
	shader.Activate();
	shader.SetUniformMat4f("u_MVP", MVP);

	// Generates Vertex Array Object and binds it
	VertexArray VA;
	VA.Bind();

	// Generate Vertex and Element Buffer Objects and link them to vertices
	VertexBuffer  VBO1(vertices, sizeof(vertices));
	IndexBuffer   IB(indices, sizeof(indices));

	std::cout << sizeof(indices);

	// Here layout will be three floats X,Y,Z and another thre for colors R,G,B
	VertexBufferLayout layout;
	// Cordinates
	layout.Push<float>(3);
	// Color
	layout.Push<float>(3);

	VA.LinkVertexBuffer(VBO1, layout);

	Renderer renderer;


	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(starter.window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	static int x_cord = 0.0f;

	// Main while loop
	while (!glfwWindowShouldClose(starter.window))
	{
		renderer.Clear();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		
		if (show_demo_window)

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{
			
			static int counter = 0;

			ImGui::Begin("Control Panel");                          // Create a window called "Hello, world!" and append into it.

			//ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			//ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderInt("Distance", &x_cord, -100, 100);       // Edit 1 float using a slider from 0.0f to 1.0f
			//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			//if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			//	counter++;
			//ImGui::SameLine();
			//ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		view = glm::translate(glm::mat4(1.0f), glm::vec3(x_cord, 0, 0));
		MVP = proj * view;
		shader.SetUniformMat4f("u_MVP", MVP);
		

		// Rendering ImGui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		renderer.Draw(VA, IB, shader);
		
		
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(starter.window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Cleanup
	VA.Delete();
	VBO1.Delete();
	IB.Delete();
	shader.Delete();

	// Cleanup ImGui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	return 0;
}