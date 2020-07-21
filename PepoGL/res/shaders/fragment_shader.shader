#version 330 core
out vec4 FragColor;  
in vec3 v_Colour;

void main()
{
	FragColor = vec4(v_Colour, 1.0);
}