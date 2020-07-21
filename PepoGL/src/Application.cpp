#include <glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

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
		 -0.5f, -0.5f, 0.0f,
		 -0.5f,  0.5f, 0.0f,
		  0.5f,  0.5f, 0.0f,
		  0.5f, -0.5f, 0.0f,
	};
	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
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

	/*
	SHADERS
	*/

	int success;
	char infoLog[512];

	// VERTEX SHADER

	const char* vertex_shader_source =
	R"glsl(
	#version 330 core
	layout(location = 0) in vec3 aPos;
	void main(){
		gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);	
	}
	)glsl";
	
	unsigned int vertex_shader;
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);
	
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
		std::cerr << "SHADER COMPILATION ERROR: [VERTEX SHADER FAILED TO COMPILE]." << std::endl;
		success = 1;
	}

	// FRAGMENT SHADER

	const char* fragment_shader_source =
	R"glsl(
	#version 330 core
	out vec4 FragColor;
	
	void main(){
		FragColor = vec4(1.0f, 0.2f, 0.2f, 1.0f);
	}
	)glsl";

	unsigned int fragment_shader;
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
		std::cerr << "SHADER COMPILATION ERROR: [FRAGMENT SHADER FAILED TO COMPILE]." << std::endl;
		success = 1;
	}

	// SHADER PROGRAM

	unsigned int shader_program;
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(fragment_shader, 512, NULL, infoLog);
		std::cerr << "PROGRAM LINKING ERROR: [SHADER PROGRAM FAILED TO LINK]." << std::endl;
		success = 1;
	}

	glUseProgram(shader_program);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);	


	std::cout << "OpenGL : [" << WINDOW_NAME << " | " << WINDOW_WIDTH << "x" << WINDOW_HEIGHT << " ] : STARTED.\n[" << glGetString(GL_VERSION) << "]" << std::endl;

	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.3f, 0.7f, 0.85f, 1.0f); // TEMPORARY
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader_program);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	return 0;
}