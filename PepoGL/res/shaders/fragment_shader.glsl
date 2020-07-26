#version 330 core
out vec4 FragColor;  

in vec2 TexCoord;

uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;

void main()
{
	FragColor = mix(texture(u_Texture1, TexCoord), texture(u_Texture2, TexCoord), vec4(texture(u_Texture2, TexCoord)).a*0.3);
}