#version 330 core 

layout (location = 0) in vec3 inputPosition;
layout (location = 1) in vec3 inputColor;

out vec3 color;

void main() 
{ 
	gl_Position = vec4(inputPosition.x, inputPosition.y, inputPosition.z, 1.0);
	color = inputColor;
}