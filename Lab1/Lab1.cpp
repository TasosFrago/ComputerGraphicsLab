#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char* vertexShaderSourceCode = 
	"#version 330 core \n"
	"\n"
	"layout (location = 0) in vec3 inputPosition; \n"
	"void main() \n"
	"{ \n"
	"gl_Position = vec4(inputPosition, 1.0); \n"
	"} \n";

const char* fragmentShaderSourceCode = 
	"#version 330 core \n"
	"\n"
	"void main() \n"
	"{ \n"
	"gl_FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0); \n"
	"} \n";

void FrameBufferSizeCallback(GLFWwindow* givenWindow, int givenWidth, int givenHeight)
{
	glViewport(0, 0, givenWidth, givenHeight);
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

	if(!window)
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


	//Data

	GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,

	};

	float pointsOfLine[]
	{
		-0.7f, -0.7f,
		-0.7f,  0.7f
	};

	// first buffer (vbo)
	unsigned int vertexBufferId;
	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// second buffer (vbo)
	unsigned int vertexBufferId2;
	glGenBuffers(1, &vertexBufferId2);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pointsOfLine), pointsOfLine, GL_STATIC_DRAW);

	// Vertex Shader
	unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertexShaderSourceCode, NULL);
	glCompileShader(vertexShaderId);
	
	// Fragment Shader
	unsigned int fragmnetShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmnetShaderId, 1, &fragmentShaderSourceCode, NULL);
	glCompileShader(fragmnetShaderId);

	// Shader Program
	unsigned int shaderProgramId = glCreateProgram();
	glAttachShader(shaderProgramId, vertexShaderId);
	glAttachShader(shaderProgramId, fragmnetShaderId);
	glLinkProgram(shaderProgramId);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmnetShaderId);

	// Game loop

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Render Using the shader program
		glUseProgram(shaderProgramId);

		// Bind the first buffer
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
		glEnableVertexAttribArray(0);

		// Draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Bind the second buffer
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId2);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);
		glEnableVertexAttribArray(0);

		// Draw the line
		glDrawArrays(GL_LINES, 0, 2);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
