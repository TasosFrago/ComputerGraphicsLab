#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Shader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float currentFrameTime = 0.0f;
float previousFrameTime = 0.0f;

float previousMousePositionX = 400.0f;
float previousMousePositionY = 300.0f;

bool firstMouse = true;

float yaw = -90.0f;
float pitch = 0.0f;

float cameraFieldOfView = 70.0f;


void FrameBufferSizeCallback(GLFWwindow* givenWindow, int givenWidth, int givenHeight)
{
	glViewport(0, 0, givenWidth, givenHeight);
}

void ProcessInput(GLFWwindow* givenWindow)
{
	if (glfwGetKey(givenWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(givenWindow, true);

	float cameraSpeed = 4.0f * deltaTime;

	if (glfwGetKey(givenWindow, GLFW_KEY_W) == GLFW_PRESS)
		cameraPosition += cameraFront * cameraSpeed;

	if (glfwGetKey(givenWindow, GLFW_KEY_S) == GLFW_PRESS)
		cameraPosition -= cameraFront * cameraSpeed;

	if (glfwGetKey(givenWindow, GLFW_KEY_D) == GLFW_PRESS)
		cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	if (glfwGetKey(givenWindow, GLFW_KEY_A) == GLFW_PRESS)
		cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void MousePosition(GLFWwindow* givenWindow, double givenMousePositionX, double givenMousePositionY)
{
	//std::cout << "X Value : " << givenMousePositionX << std::endl;
	//std::cout << "Y Value : " << givenMousePositionY << std::endl;

	if (firstMouse)
	{
		previousMousePositionX = givenMousePositionX;
		previousMousePositionY = givenMousePositionY;

		firstMouse = false;
	}

	float offsetX = givenMousePositionX - previousMousePositionX;
	float offsetY = previousMousePositionY - givenMousePositionY;
	previousMousePositionX = givenMousePositionX;
	previousMousePositionY = givenMousePositionY;

	float mouseSensitivity = 0.1f;

	yaw += offsetX * mouseSensitivity;
	pitch += offsetY * mouseSensitivity;

	if (pitch > 89.0f)
		pitch = 89.0f;
	else if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	cameraFront = glm::normalize(direction);

}

void MouseScroll(GLFWwindow* givenWindow, double givenScrollPositionX, double givenScrollPositionY)
{
	cameraFieldOfView -= givenScrollPositionY * 3;

	if (cameraFieldOfView > 70.0f)
		cameraFieldOfView = 70.0f;
	else if (cameraFieldOfView < 1.0f)
		cameraFieldOfView = 1.0f;
}

std::ostream& operator<<(std::ostream& givenOutputStream, glm::mat4& givenMatrix4)
{
	float* firstElement = glm::value_ptr(givenMatrix4);

	for (int i = 1; i <= 16; i++)
	{
		givenOutputStream << *firstElement << "\t";

		firstElement++;

		if (i % 4 == 0)
		{
			givenOutputStream << "\n";
		}
	}

	return givenOutputStream;
}

int main()
{
	// Initialization

	if (!glfwInit())
	{
		std::cout << "Failed to initialize glfw!" << std::endl;
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Lab3", NULL, NULL);

	if (!window)
	{
		std::cout << "Failed to initialize the window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Set the callback function
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);

	glfwSetCursorPosCallback(window, MousePosition);

	glfwSetScrollCallback(window, MouseScroll);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize glew!" << std::endl;
		glfwTerminate();
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	//Data


	GLfloat vertices[] = {
		//position            //color             
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0,
		-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0,

		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0,
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0,

		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

		0.5f,  0.5f,  0.5f,  0.0f, 0.5f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 0.5f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.5f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 0.5f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.5f,
		0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.5f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.5f,

		-0.5f,  0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.5f, 0.0f, 0.0f
	};

	glm::vec3 cubePositions[] =
	{
	  glm::vec3(0.0f,  0.0f,  0.0f),
	  glm::vec3(2.0f,  5.0f, -15.0f),
	  glm::vec3(-1.5f, -2.2f, -2.5f),
	  glm::vec3(-3.8f, -2.0f, -12.3f),
	  glm::vec3(2.4f, -0.4f, -3.5f),
	  glm::vec3(-1.7f,  3.0f, -7.5f),
	  glm::vec3(1.3f, -2.0f, -2.5f),
	  glm::vec3(1.5f,  2.0f, -2.5f),
	  glm::vec3(1.5f,  0.2f, -1.5f),
	  glm::vec3(-1.3f,  1.0f, -1.5f)
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


	Shader shaderProgram("./Shaders/VertexShaderLab3.glsl", "./Shaders/FragmentShaderLab3.glsl");

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//glm::vec4 point = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
	//glm::mat4 transform = glm::mat4(1.0f);
	//transform = glm::translate(transform, glm::vec3(2.0f, 1.0f, 0.0f));
	//point = transform * point;

	//std::cout << point.x << point.y << point.z << std::endl;

	glm::mat4 identity = glm::mat4(1.0f);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LESS);

	// Game loop

	while (!glfwWindowShouldClose(window))
	{
		float time = glfwGetTime();

		currentFrameTime = time;
		deltaTime = currentFrameTime - previousFrameTime;
		previousFrameTime = currentFrameTime;

		ProcessInput(window);

		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render Using the shader program
		shaderProgram.use();

		glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);

		/*float radius = 20.0f;
		float cameraX = sin(time) * radius;
		float cameraY = cos(time) * radius;

		glm::vec3 cameraCircle = glm::vec3(cameraX, 0.0f, cameraY);*/

		glm::mat4 view;
		view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

		std::cout << view << std::endl;

		int viewLocation = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

		glm::mat4 projection;

		// 2D
		//projection = glm::ortho(-5.0f, 5.0f, -6.0f, 6.0f, -15.0f, 18.0f); // the values were chosen to fit the cube positions in each axis

		// 3D
		projection = glm::perspective(glm::radians(cameraFieldOfView), 800.0f / 600.0f, 0.3f, 100.0f);

		int projectionLocation = glGetUniformLocation(shaderProgram.ID, "projection");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

		for (int i = 0; i < 10; i++)
		{
			glm::mat4 model;


			model = glm::translate(identity, cubePositions[i]);
			model = glm::rotate(model, glm::radians(20.0f) * i, glm::vec3(1.0f, 0.3f, 0.5f));

			int modelLocation = glGetUniformLocation(shaderProgram.ID, "model");
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
