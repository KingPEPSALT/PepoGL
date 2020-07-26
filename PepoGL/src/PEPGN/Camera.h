#pragma once
#include "vendor/glm/glm.hpp"
namespace PEPGN {
	struct Camera {
		glm::vec3 position;
		glm::vec3 direction;
		glm::vec3 cameraUp, cameraRight;
		Camera(const glm::vec3& pos);
		Camera(const glm::vec3& pos, const glm::vec3& dir);
	};
}