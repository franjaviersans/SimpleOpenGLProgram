#version 450 core

in vec3 vFinalColor;

out vec4 vFragColor;

void main(void)
{
	vFragColor = vec4(vFinalColor,1.0f);
}