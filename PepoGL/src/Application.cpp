#include <glew.h>
#include <GLFW/glfw3.h>
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/glm/gtc/type_ptr.hpp"
#include "ErrorColour.h"

#include <iostream>

#include "Shader.h"

#include "vendor/stb_image/stb_image.h"


static int binaryHandleInput(GLFWwindow* window, GLenum pos, GLenum neg) {
	if (glfwGetKey(window, pos) == GLFW_PRESS) {
		return 1;
	}
	else if (glfwGetKey(window, neg) == GLFW_PRESS) {
		return -1;
	}
	return 0;
}

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
	const float ASPECT_RATIO = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT);

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
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	
	//unsigned int indices[] = {
	//	0, 1, 2,
	//	2, 3, 0
	//};

	
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//unsigned int ebo;
	//glGenBuffers(1, &ebo);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// texture
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);

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
	const char* texture_path = "./res/textures/minecraft_grass_side.png";
	std::string t_file_name = static_cast<std::string>(texture_path).substr(static_cast<std::string>(texture_path).find_last_of("/\\") + 1);
	unsigned char* data = stbi_load(texture_path, &width, &height, &no_chans, STBI_rgb);

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
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	texture_path = "./res/textures/awesomeface.png";
	t_file_name = static_cast<std::string>(texture_path).substr(static_cast<std::string>(texture_path).find_last_of("/\\") + 1);
	data = stbi_load(texture_path, &width, &height, &no_chans, STBI_rgb_alpha);

	if (data) {
		std::cout << CONSOLE_GREEN << "TEXTURE LOADING SUCCESS: [LOADED: \"" << t_file_name << "\"]." << std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		
		std::cout << CONSOLE_RED << "TEXTURE LOADING ERROR: [FAILED TO LOAD: \"" << t_file_name << "\"]." << std::endl;
	}

	stbi_image_free(data);

	glm::mat4 model(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 view(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), ASPECT_RATIO, 0.1f, 100.0f);


	shader.use();
	shader.setInt("u_Texture1", 0);
	shader.setInt("u_Texture2", 1);


	///////////////////
	//				 //
	//   RENDERING   //
	//				 //
	///////////////////

	std::cout << CONSOLE_BLUE << "\nOpenGL STARTED: [ \"" << WINDOW_NAME << "\" | " << WINDOW_WIDTH << "x" << WINDOW_HEIGHT << " ]\nVERSION: [" << glGetString(GL_VERSION) << "]" << std::endl;

	float fElapsedTime;
	//int u_Colour = glGetUniformLocation(shader_program, "u_Colour");

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		glClearColor((135.0f/255.0f), (206.0f/255.0f), (235.0f/255.0f), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		fElapsedTime = glfwGetTime();
		//glUniform4f(u_Colour, redValue, 0.4f, blueValue, 1.0f);

		model = glm::mat4(1.0f);
		model = glm::rotate(model, fElapsedTime, glm::vec3(0.5f, 1.0f, 0.0f));

		shader.setFloatM4("model", model, GL_FALSE);
		shader.setFloatM4("view", view, GL_FALSE);
		shader.setFloatM4("proj", projection, GL_FALSE);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glBindVertexArray(vao);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		//glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(unsigned int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	std::cout << CONSOLE_RESET << std::endl;
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	//glDeleteBuffers(1, &ebo);
	glfwDestroyWindow(window);
	return 0;
}
