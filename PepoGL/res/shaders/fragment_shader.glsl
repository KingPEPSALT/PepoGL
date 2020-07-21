#version 330 core
out vec4 FragColor;  

in vec3 v_Colour;
in vec2 TexCoord;

uniform sampler2D u_Texture;

void main()
{
	FragColor = texture(u_Texture, TexCoord) * vec4(v_Colour, 1.0);
}