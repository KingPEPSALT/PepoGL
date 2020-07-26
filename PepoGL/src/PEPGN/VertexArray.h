#pragma once
#include "BufferObject.h"
namespace PEPGN {
	class VertexArray {
		unsigned int ID;
		bool isSetup;
	public:

		VertexArray(bool doSetup=false);
		void bind() const;
		VertexArray& bindBuffer(BufferObject bufferObj);
		void unbind() const;
		void setup();
	};

}