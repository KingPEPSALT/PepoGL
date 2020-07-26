#include "VertexArray.h"
#include <glew.h>
#include <GLFW/glfw3.h>
namespace PEPGN{
	VertexArray::VertexArray(bool doSetup) : isSetup(doSetup) {
		if (doSetup) this->setup();
	}

	void VertexArray::bind() const {
		glBindVertexArray(this->ID);
	}

	VertexArray& VertexArray::bindBuffer(BufferObject bufferObj) {
		this->bind();
		bufferObj.bind();
		this->unbind();
		return *this;
	}

	void VertexArray::unbind() const {
		glBindVertexArray(0);
	}
	
	void VertexArray::setup() {
		if (!this->isSetup) {
			glGenVertexArrays(1, &(this->ID));
			glBindVertexArray(this->ID);
			this->isSetup = true;
		}
	}
}