#version 330 core

layout(location = 0) in vec3 inputPosition;
layout(location = 1) in vec3 inputColor;

out vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(inputPosition.x, inputPosition.y, inputPosition.z, 1.0);
	color = inputColor;
}