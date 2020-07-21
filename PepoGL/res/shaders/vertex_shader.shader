#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColour;

uniform vec3 u_Translation;

out vec3 v_Colour;

void main() {
	gl_Position = vec4(aPos*u_Translation, 1.0);
	v_Colour = aColour;
}