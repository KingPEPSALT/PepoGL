#version 330 core
out vec4 FragColor;  
in vec3 v_Colour;
in vec3 position;

void main()
{
	float dist = sqrt(position.x * position.x + position.y * position.y);
	FragColor = vec4(dist*1.3, 0.0, 0.0, 1.0);
}