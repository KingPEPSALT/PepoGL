#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColour;
layout(location = 2) in vec2 aTexCoord;

out vec3 v_Colour;
out vec2 TexCoord;

uniform vec3 aspect_ratio;

void main() {
	gl_Position = vec4(aPos*aspect_ratio, 1.0);
	v_Colour = aColour;
	TexCoord = aTexCoord;
}