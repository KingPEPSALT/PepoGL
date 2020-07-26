#include <glew.h>
#include "BufferObject.h"

namespace PEPGN {
	BufferObject::BufferObject(GLenum t, void* data, GLenum usage) : target(t) {
		glGenBuffers(1, &(this->ID));
		this->bind();
		glBufferData(this->target, sizeof(data), data, usage);
		this->unbind();
	}

	void BufferObject::bind() const {
		glBindBuffer(this->target, this->ID);
	}

	void BufferObject::unbind() const {
		glBindBuffer(this->target, 0);
	}
}