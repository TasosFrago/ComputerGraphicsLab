#version 330 core

//uniform float greenChanel;

in vec3 color;

void main()
{
	gl_FragColor = vec4(color, 1.0);
}