#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

void FrameBufferSizeCallback(GLFWwindow* givenWindow, int givenWidth, int givenHeight)
{
	glViewport(0, 0, givenWidth, givenHeight);
}

void ProcessInput(GLFWwindow* givenWindow)
{
	if (glfwGetKey(givenWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(givenWindow, true);
}


int main()
{
	// Initialization

	if (!glfwInit())
	{
		std::cout << "Failed to initialize glfw!" << std::endl;
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Lab1", NULL, NULL);

	if (!window)
	{
		std::cout << "Failed to initialize the window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Set the callback function
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize glew!" << std::endl;
		glfwTerminate();
		return -1;
	}

	const char* glsl_version = "#version 330";
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	//Data
	//GLfloat vertices[] =
	//{
	//	-0.5f, -0.5f, 0.0f,
	//	 0.5f, -0.5f, 0.0f,
	//	 0.0f,  0.5f, 0.0f,
	//};

	// //RECTANGLE - VBO only
	//GLfloat vertices[] =
	//{
	//	// first triangle
	//	0.5f, 0.5f, 0.0f,     // top right
	//	0.5f, -0.5f, 0.0f,   // bottom right
	//-0.5f, 0.5f, 0.0f,  // top left
	//	// second triangle
	//	0.5f, -0.5f, 0.0f,   // bottom right
	//	-0.5f, -0.5f, 0.0f, // bottom left
	//	-0.5f, 0.5f, 0.0f  // top left
	//};

	//RECTANGLE - VBO and EBO - part1: VBO
	//GLfloat  vertices[] =
	//{
	//	0.5f, 0.5f, 0.0f,    // top right
	//	0.5f, -0.5f, 0.0f,   // bottom right
	//	-0.5f, -0.5f, 0.0f, // bottom left
	//	-0.5f, 0.5f, 0.0f   // top left
	//};

	//RECTANGLE - VBO and EBO - part1: VBO (with color)
	GLfloat  vertices[] =
	{
		 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,    // top right
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
		-0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 1.0f // top left
	};


	// first buffer (vbo)
	unsigned int vertexBufferId;
	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//RECTANGLE - VBO and EBO - part2: EBO
	GLuint indices[] =
	{
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
	};

	unsigned int elementBufferId;
	glGenBuffers(1, &elementBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	Shader shaderProgram("./Shaders/VertexShaderLab2.glsl", "./Shaders/FragmentShaderLab2.glsl");

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//glLineWidth(10.0f);

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Hello, world!");

		ImGui::ColorEdit3("clear color", (float*)&clear_color);

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Render Using the shader program
		shaderProgram.use();

		//float time = glfwGetTime();
		//float greenChanel = sin(time) * 0.5f + 0.5f;

		int uniformLocation = glGetUniformLocation(shaderProgram.ID, "color1");
		glUniform3f(uniformLocation, clear_color.x, clear_color.y, clear_color.z);

		// Draw the triangle
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
