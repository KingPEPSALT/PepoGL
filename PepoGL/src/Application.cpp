#include <glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Shader.h"


int main() {

	//INITIALISATIONS START

	GLFWwindow* window;

	if (!glfwInit()) {
		std::cerr << "INITIALISATION ERROR: [GLFW DID NOT INITIALISE]." << std::endl;
		return -1;
	}

	const int WINDOW_WIDTH = 640;
	const int WINDOW_HEIGHT = 480;
	const char* WINDOW_NAME = "PepoGL";

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwSwapInterval(1);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, NULL, NULL);

	if (!window) {
		std::cerr << "INITIALISATION ERROR: [WINDOW DID NOT CREATE]." << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cerr << "INITIALISATION ERROR: [GLEW DID NOT INITIALISE]." << std::endl;
		return -1;
	}

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int width, int height){ glViewport(0, 0, width, height); });

	//INITIALISATIONS END

	std::cout << "INITIALISATION SUCCESS: [SUCCESFULLY INITIALISED GLEW AND GLFW].\n" << std::endl;

	// VERTEX BUFFER

	float vertices[] = {
		  0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	};

	unsigned int indices[] = {
		0, 1, 2,
	};

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	////////////////////
	//    SHADERS     //
	////////////////////

	Shader shader("D:\\pepsalt\\Documents\\Developer\\other-dev\\cpp\\VSTUDIO\\PepoGL\\PepoGL\\res\\shaders\\vertex_shader.shader",
		"D:\\pepsalt\\Documents\\Developer\\other-dev\\cpp\\VSTUDIO\\PepoGL\\PepoGL\\res\\shaders\\fragment_shader.shader");

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	///////////////////
	//   RENDERING   //
	///////////////////

	std::cout << "OpenGL : [" << WINDOW_NAME << " | " << WINDOW_WIDTH << "x" << WINDOW_HEIGHT << " ] : STARTED.\n[" << glGetString(GL_VERSION) << "]" << std::endl;

	float elapsedTime;
	//int u_Colour = glGetUniformLocation(shader_program, "u_Colour");

	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // TEMPORARY
		glClear(GL_COLOR_BUFFER_BIT);

		elapsedTime = glfwGetTime();
		shader.use();
		shader.setFloat3("u_Translation", -1.0f, -1.0f, -1.0f);
		//glUniform4f(u_Colour, redValue, 0.4f, blueValue, 1.0f);

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(unsigned int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	return 0;
}