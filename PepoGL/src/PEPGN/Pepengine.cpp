#include <glew.h>
#include <GLFW/glfw3.h>
#include "Pepengine.h"
#include <iostream>
#include "ConsoleColour.h"

namespace PEPGN {

	int init() {
		if (!initGLFW()) return -1;
		if (!window->getWindow()) glfwMakeContextCurrent(window->getWindow());
		else return -1;
		if (!initGLEW()) return -1;
		glViewport(0, 0, window->getWidth(), window->getHeight());
		glfwSetFramebufferSizeCallback(window->getWindow(), [](GLFWwindow* win, int width, int height) {glViewport(0, 0, width, height); });
		std::cout << CONSOLE_GREEN << "INITIALISATION SUCCESS: [SUCCESFULLY INITIALISED GLEW AND GLFW].\n" << std::endl;
		return 0;
	}

	bool initGLFW(int swapInterval) {
		if (!glfwInit()) {
			std::cout << CONSOLE_RED << "INIT ERROR: [GLFW DID NOT INITIALISE]." << std::endl;
			return false;
		};
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwSwapInterval(swapInterval);

		return true;
	}
	bool initGLEW() {
		if (glewInit() != GLEW_OK) {
			std::cout << CONSOLE_RED << "INIT ERROR: [GLEW DID NOT INITIALISE CORRECTLY]" << std::endl;
			return false;
		}
		return true;
	}
}