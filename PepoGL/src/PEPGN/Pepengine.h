#pragma once
#include "Window.h"

namespace PEPGN {
	Window* window;
	int init();
	bool initGLFW(int swapInterval=1);
	bool initGLEW();
}