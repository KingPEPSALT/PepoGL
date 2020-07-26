#include "Camera.h"

namespace PEPGN {
	Camera::Camera(const glm::vec3& pos) : position(pos), direction(glm::vec3(0.0f, 0.0f, 1.0f)), cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)), cameraRight(glm::vec3(1.0f, 0.0f, 0.0f)) {};
	Camera::Camera(const glm::vec3& pos, const glm::vec3& dir) : position(pos), direction(glm::normalize(dir)) {
		cameraRight = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), direction));
		cameraUp = glm::normalize(glm::cross(direction, cameraRight));
	}

}