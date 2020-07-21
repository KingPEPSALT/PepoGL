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
	
	//INITIALISATIONS END

	while (!glfwWindowShouldClose(window)) {

	}

	glfwDestroyWindow(window);
	return 0;
}