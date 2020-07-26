#include "InputListener.h"

namespace PEPGN {

	bool InputMap::isPressed(unsigned int inp_code) {
		auto it = inputMap.find(inp_code);
		if (it == inputMap.end()) return false;
		return it->second;
	};


	InputListener::InputListener(const std::vector<unsigned int>& k, const std::vector<unsigned int>& m) {
		keyListen = std::vector<unsigned int>(k.begin(), k.end());
		mouseListen = std::vector<unsigned int>(m.begin(), m.end());
	};


	void InputListener::listenForInput() {
		for (auto k : keyListen) (glfwGetKey(window->getWindow(), k) == GLFW_PRESS) ? keyMap.pressed(k) : keyMap.released(k);
		for (auto m : mouseListen) (glfwGetMouseButton(window->getWindow(), m) == GLFW_PRESS) ? mouseMap.pressed(m) : mouseMap.released(m);
	};

	void Mouse::cursor_move_callback(GLFWwindow* window, double xpos, double ypos) {
		position.x = xpos;
		position.y = ypos;
		offset.x = position.x - lastPos.x;
		offset.y = position.y - lastPos.y;
		lastPos.x = xpos;
		lastPos.y = ypos;
	};
}