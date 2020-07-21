#include "Shader.h"
#include <fstream>
#include <sstream>

#include <iostream>
#include <string_view>

Shader::Shader(const char* vertex_source_path, const char* fragment_source_path) {

	//READING SHADERS FROM FILE

	std::string vertex_str, fragment_str;
	std::ifstream vFile, fFile;
	vFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		vFile.open(vertex_source_path);
		fFile.open(fragment_source_path);

		std::stringstream vStream, fStream;

		vStream << vFile.rdbuf();
		fStream << fFile.rdbuf();

		vFile.close();
		fFile.close();

		vertex_str = vStream.str();
		fragment_str = fStream.str();	
	}
	catch (std::ifstream::failure e) {
		std::cerr << "FILE READING ERROR: [FAILED TO READ SHADER FILE].\n" << e.what() << std::endl;
	}
	const char* vertex_source = vertex_str.c_str();
	const char* fragment_source = fragment_str.c_str();

	//CREATING SHADERS & PROGRAM

	unsigned int vertex_shader, fragment_shader;
	int success;
	char infolog[512];

	//VERTEX SHADER

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_source, NULL);
	glCompileShader(vertex_shader);

	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex_shader, 512, NULL, infolog);
		std::cerr << "SHADER COMPILATION ERROR: [FAILED TO COMPILE VERTEX SHADER].\nINFO LOG:\n" << infolog << std::endl;
		success = 1; memset(infolog, 0, sizeof(infolog));
	}

	//FRAGMENT SHADER

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_source, NULL);
	glCompileShader(fragment_shader);

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment_shader, 512, NULL, infolog);
		std::cerr << "SHADER COMPILATION ERROR: [FAILED TO COMPILE FRAGMENT SHADER].\nINFO LOG:\n" << infolog << std::endl;
		success = 1; memset(infolog, 0, sizeof(infolog));
	}

	//PROGRAM

	this->ID = glCreateProgram();
	glAttachShader(this->ID, vertex_shader);
	glAttachShader(this->ID, fragment_shader);
	glLinkProgram(this->ID);

	glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->ID, 512, NULL, infolog);
		std::cerr << "PROGRAM LINKING ERROR: [FAILED TO LINK PROGRAM].\nINFO LOG:\n" << infolog << std::endl;
		success = 1; memset(infolog, 0, sizeof(infolog));
	}

	//DELETE LINKED SHADERS

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

}

void Shader::use() {
	glUseProgram(this->ID);
}

void Shader::setBool(const std::string& uniform_name, bool value) const {
	glUniform1i(glGetUniformLocation(this->ID, uniform_name.c_str()), static_cast<int>(value));
}
void Shader::setInt(const std::string& uniform_name, int value) const {
	glUniform1i(glGetUniformLocation(this->ID, uniform_name.c_str()), value);
}
void Shader::setFloat(const std::string& uniform_name, float value) const {
	glUniform1f(glGetUniformLocation(this->ID, uniform_name.c_str()), value);
}
void Shader::setFloat3(const std::string& uniform_name, float v1, float v2, float v3) const {
	glUniform3f(glGetUniformLocation(this->ID, uniform_name.c_str()), v1, v2, v3);
}
