#include <glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Shader.h"

#include "vendor/stb_image/stb_image.h"

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
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int width, int height){glViewport(0, 0, width, height);});

	//INITIALISATIONS END

	std::cout << "INITIALISATION SUCCESS: [SUCCESFULLY INITIALISED GLEW AND GLFW].\n" << std::endl;

	// VERTEX BUFFER

	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};
	
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
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

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// colour
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	// texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	////////////////////
	//    SHADERS     //
	//   TEXTURES     //
	////////////////////

	Shader shader("./res/shaders/vertex_shader.glsl",
		"./res/shaders/fragment_shader.glsl");

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height, no_chans;
	const char* texture_path = "./res/textures/molten.jpg";
	unsigned char* data = stbi_load(texture_path, &width, &height, &no_chans, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D); 
	}
	else {
		std::cout << "TEXTURE LOADING ERROR: [FAILED TO LOAD TEXTURE].\nPATH:\n" << texture_path << std::endl;
	}

	stbi_image_free(data);

	shader.use();
	shader.setInt("u_Texture", 0);
	shader.setFloat3("aspect_ratio", static_cast<float>(WINDOW_HEIGHT) / static_cast<float>(WINDOW_WIDTH), 1.0f, 1.0f);

	
	///////////////////
	//   RENDERING   //
	///////////////////

	std::cout << "OpenGL : [" << WINDOW_NAME << " | " << WINDOW_WIDTH << "x" << WINDOW_HEIGHT << " ] : STARTED.\n[" << glGetString(GL_VERSION) << "]" << std::endl;

	float elapsedTime;
	//int u_Colour = glGetUniformLocation(shader_program, "u_Colour");
	
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//elapsedTime = glfwGetTime();
		//glUniform4f(u_Colour, redValue, 0.4f, blueValue, 1.0f);
		
		//glBindTextureUnit(GL_TEXTURE0, texture);

		//glBindTexture(GL_TEXTURE_2D, texture);
		//glActiveTexture(GL_TEXTURE0);

		shader.use();
		shader.setInt("u_Texture", 0);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(unsigned int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		static GLenum error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << error << "\n" << std::endl;
			
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	return 0;
}