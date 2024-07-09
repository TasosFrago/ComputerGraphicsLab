#version 330 core 

uniform vec3 color1;

in vec3 color;

void main() 
{ 
	gl_FragColor = vec4(color1, 1.0);
}