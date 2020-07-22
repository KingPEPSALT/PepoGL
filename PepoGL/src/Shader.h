#pragma once
#include <glew.h>
#include <string>
#include "vendor/glm/glm.hpp"

class Shader {
	int ID;
public:
	Shader(const char* vertex_source_path, const char* fragment_source_path);
	
	void use();

	void setBool(const std::string& uniform_name, bool value) const;
	void setInt(const std::string& uniform_name, int value) const;
	void setFloat(const std::string& uniform_name, float value) const;
	void setFloat3(const std::string& uniform_name, float v1, float v2, float v3) const;
	void setFloatM4(const std::string& uniform_name, const glm::mat4& matrix, GLenum column_major) const;
};