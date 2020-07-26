#pragma once
#include <GLFW/glfw3.h>
namespace PEPGN {
	class Window {
		const char* name;
		int width, height;
		GLFWwindow* window;
	public:
		Window(const char* n, int w, int h) : name(n), width(w), height(h) { window = glfwCreateWindow(w, h, n, NULL, NULL); };
		inline float aspect_ratio() const { return static_cast<float>(height) / static_cast<float>(width); };
		inline int getWidth() const { return width; };
		inline int getHeight() const { return height; };
		inline GLFWwindow* getWindow() const { return window; };
		inline void swapBuffer() const { glfwSwapBuffers(this->window); };
	};
}