#pragma once
#include "vendor/stb_image/stb_image.h"
#include <string>
namespace PEPGN {
	struct Texture {
		
		int stbi_e;
		const char* path;
		int height, width, channels;
		unsigned char* loaded_data;

		void load();
		void free();
		
		inline std::string filename() const{
			return static_cast<std::string>(path).substr(static_cast<std::string>(path).find_last_of("/\\") + 1);
		}

	};

	class GLTexture {
		Texture texture;
		unsigned int ID;

	public:
		GLTexture(const char* p, int s_e, GLenum wrap_t_param = GL_CLAMP_TO_EDGE, GLenum wrap_s_param = GL_CLAMP_TO_EDGE, GLenum min_filter_param = GL_LINEAR, GLenum max_filter_param = GL_LINEAR);
		void bind() const;
		void unbind() const;
		void initImage();
		void setParam(GLenum name, GLenum param);
		void init(GLenum wrap_t_param = GL_CLAMP_TO_EDGE, GLenum wrap_s_param = GL_CLAMP_TO_EDGE, GLenum min_filter_param = GL_LINEAR, GLenum max_filter_param = GL_LINEAR) const;
	};
}