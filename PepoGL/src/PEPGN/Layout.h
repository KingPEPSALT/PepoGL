#pragma once
#include <glew.h>
#include <GLFW/glfw3.h>
#include <vector>
namespace PEPGN {
	struct LayoutElement {
		unsigned int count;
		unsigned int type;
		unsigned char normalised;

		static unsigned int getSizeOfType(unsigned int type) {
			switch (type) {
			case GL_UNSIGNED_INT:
				return 4;
			case GL_UNSIGNED_BYTE:
				return 1;
			case GL_FLOAT:
				return 4;
			}
		}
	};

	class Layout {
		std::vector<LayoutElement> elements;
		unsigned int stride;
	public:
		Layout() : stride(0) {};
		template <typename T>
		void push(unsigned int count) {
			static_assert(false);
		}
		template<>
		void push<int>(unsigned int count) {
			elements.push_back({ count, GL_INT, GL_FALSE });
			stride += LayoutElement::getSizeOfType(GL_UNSIGNED_INT) * count;
		};
		template<>
		void push<float>(unsigned int count) {
			elements.push_back({ count, GL_FLOAT, GL_FALSE });
			stride += LayoutElement::getSizeOfType(GL_FLOAT) * count;
		};
		template<>
		void push<unsigned char>(unsigned int count) {
			elements.push_back({ count, GL_UNSIGNED_BYTE, GL_FALSE });
			stride += LayoutElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
		};
		inline const std::vector<LayoutElement>& getElements() { return elements; };
		inline unsigned int getStride() { return stride; };
	};
}