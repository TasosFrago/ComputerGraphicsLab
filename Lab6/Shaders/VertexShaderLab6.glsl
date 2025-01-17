#version 330 core

layout(location = 0) in vec3 inputPosition;
layout(location = 1) in vec3 inputNormal;
layout(location = 2) in vec2 inputTextureCoordiantes;

out vec3 normal;
out vec3 fragmentPosition;
out vec2 textureCoordiantes;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat3 normalTransformation;

void main()
{
	gl_Position = projection * view * model * vec4(inputPosition.x, inputPosition.y, inputPosition.z, 1.0);
	normal = normalTransformation * inputNormal;
	textureCoordiantes = inputTextureCoordiantes;


	// 4x4 * 4x1 = 4 x 1 -> 3 x 1
	fragmentPosition = vec3(model * vec4(inputPosition, 1.0f));
}