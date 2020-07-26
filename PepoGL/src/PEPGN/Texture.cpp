#include <glew.h>
#include "Texture.h"
namespace PEPGN {
	
	void Texture::load() {
		stbi_set_flip_vertically_on_load(true);
		loaded_data = stbi_load(path, &width, &height, &channels, stbi_e);
		stbi_set_flip_vertically_on_load(false);
	};
	
	void Texture::free() {
		stbi_image_free(this->loaded_data);
	}

	GLTexture::GLTexture(const char* p, int s_e, GLenum wrap_t_param, GLenum wrap_s_param, GLenum min_filter_param, GLenum mag_filter_param) {
		glGenTextures(1, &(this->ID));
		this->init(wrap_t_param, wrap_s_param, min_filter_param, mag_filter_param);
		texture.path = p;
		texture.stbi_e = s_e;
		texture.load();
		if (texture.loaded_data) {
			this->initImage();
		}
	};
	
	void GLTexture::bind() const {
		glBindTexture(GL_TEXTURE_2D, this->ID);
	};

	void GLTexture::unbind() const {
		glBindTexture(GL_TEXTURE_2D, 0);
	};

	void GLTexture::initImage() {
		GLenum g_e = GL_RGB + (texture.stbi_e - 3);
		this->bind();
		glTexImage2D(GL_TEXTURE_2D, 0, g_e, texture.width, texture.height, 0, g_e, GL_UNSIGNED_BYTE, texture.loaded_data);
		this->unbind();
	};

	void GLTexture::init(GLenum wrap_t_param, GLenum wrap_s_param, GLenum min_filter_param, GLenum mag_filter_param) const {
		this->bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t_param);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s_param);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter_param);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter_param);
		this->unbind();
	};
	void GLTexture::setParam(GLenum name, GLenum param) {
		this->bind();
		glTexParameteri(GL_TEXTURE_2D, name, param);
		this->unbind();
	}

}