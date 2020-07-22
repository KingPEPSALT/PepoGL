#include <glew.h>
#include <GLFW/glfw3.h>
#include "ErrorColour.h"

#include <iostream>

#include "Shader.h"

#include "vendor/stb_image/stb_image.h"

int main() {
	
	//INITIALISATIONS START
	GLFWwindow* window;

	if (!glfwInit()) {
		
		std::cout << CONSOLE_RED << "INITIALISATION ERROR: [GLFW DID NOT INITIALISE]." << std::endl;
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
		
		std::cout << CONSOLE_RED << "INITIALISATION ERROR: [WINDOW DID NOT CREATE]." << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cout << CONSOLE_RED << "INITIALISATION ERROR: [GLEW DID NOT INITIALISE]." << std::endl;
		return -1;
	}

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int width, int height){glViewport(0, 0, width, height);});

	//INITIALISATIONS END
	std::cout << CONSOLE_GREEN << "INITIALISATION SUCCESS: [SUCCESFULLY INITIALISED GLEW AND GLFW].\n" << std::endl;

	// VERTEX BUFFER

	float vertices[] = {
		// positions          // colors           // texture
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
	//				  //
	//    SHADERS     //
	//    TEXTURES    //
	//                //
	////////////////////

	Shader shader("./res/shaders/vertex_shader.glsl",
		"./res/shaders/fragment_shader.glsl");

	stbi_set_flip_vertically_on_load(true);

	unsigned int textures[2];
	glGenTextures(2, textures);
	glBindTexture(GL_TEXTURE_2D, textures[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height, no_chans;
	const char* texture_path = "./res/textures/container.jpg";
	std::string t_file_name = static_cast<std::string>(texture_path).substr(static_cast<std::string>(texture_path).find_last_of("/\\") + 1);
	unsigned char* data = stbi_load(texture_path, &width, &height, &no_chans, 3);

	if (data) {
		std::cout << CONSOLE_GREEN << "TEXTURE LOADING SUCCESS: [LOADED: \"" << t_file_name << "\"]." << std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << CONSOLE_RED << "TEXTURE LOADING ERROR: [FAILED TO LOAD:\"" << t_file_name << "\"]." << std::endl;
	}

	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	texture_path = "./res/textures/awesomeface.png";
	t_file_name = static_cast<std::string>(texture_path).substr(static_cast<std::string>(texture_path).find_last_of("/\\") + 1);
	data = stbi_load(texture_path, &width, &height, &no_chans, 4);

	if (data) {
		std::cout << CONSOLE_GREEN << "TEXTURE LOADING SUCCESS: [LOADED: \"" << t_file_name << "\"]." << std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		
		std::cout << CONSOLE_RED << "TEXTURE LOADING ERROR: [FAILED TO LOAD: \"" << t_file_name << "\"]." << std::endl;
	}

	stbi_image_free(data);

	shader.use();
	shader.setInt("u_Texture1", 0);
	shader.setInt("u_Texture2", 1);
	shader.setFloat3("aspect_ratio", static_cast<float>(WINDOW_HEIGHT) / static_cast<float>(WINDOW_WIDTH), 1.0f, 1.0f);

	
	///////////////////
	//				 //
	//   RENDERING   //
	//				 //
	///////////////////

	std::cout << CONSOLE_BLUE << "\nOpenGL STARTED: [ \"" << WINDOW_NAME << "\" | " << WINDOW_WIDTH << "x" << WINDOW_HEIGHT << " ]\nVERSION: [" << glGetString(GL_VERSION) << "]" << std::endl;

	//float elapsedTime;
	//int u_Colour = glGetUniformLocation(shader_program, "u_Colour");

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//elapsedTime = glfwGetTime();
		//glUniform4f(u_Colour, redValue, 0.4f, blueValue, 1.0f);
		

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textures[1]);


		shader.use();
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(unsigned int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	std::cout << CONSOLE_RESET << std::endl;
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glfwDestroyWindow(window);
	return 0;
}