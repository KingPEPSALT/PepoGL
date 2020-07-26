#pragma once
#include <unordered_map>
#include <GLFW/glfw3.h>
#include "Window.h"
#include <vector>
#include "vendor/glm/glm.hpp"
namespace PEPGN {
	
	struct InputMap {
		inline void pressed(unsigned int inp_code) { inputMap[inp_code] = true; };
		inline void released(unsigned int inp_code) { inputMap[inp_code] = false; };
		bool isPressed(unsigned int inp_code);

	private:
		std::unordered_map<unsigned int, bool> inputMap;
	};

	class InputListener {

		Window* window;
		InputMap keyMap, mouseMap;
		std::vector<unsigned int> keyListen, mouseListen;


	public:
		InputListener(const std::vector<unsigned int>& k, const std::vector<unsigned int>& m);	
		void listenForInput();
		inline bool isKeyPressed(unsigned int key) { return keyMap.isPressed(key); };
		inline bool isMousePressed(unsigned int button) { return mouseMap.isPressed(button); };
	};

	struct Mouse {
	
		void cursor_move_callback(GLFWwindow* window, double xpos, double ypos);
		inline const glm::vec2& getPosition() const {
			return position;
		}
		inline const glm::vec2& getOffset() const {
			return offset;
		}
		inline const glm::vec2& getLastPosition() const {
			return lastPos;
		}
	private:
		glm::vec2 position;
		glm::vec2 offset;
		glm::vec2 lastPos;


	};

}