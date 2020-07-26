#pragma once
#include <glew.h>
#include <GLFW/glfw3.h>
namespace PEPGN {
	class BufferObject {
		GLenum target;
		unsigned int ID;
	public:
		BufferObject(GLenum t, void* data, GLenum usage);
		void bind() const;
		void unbind() const;
	};
}