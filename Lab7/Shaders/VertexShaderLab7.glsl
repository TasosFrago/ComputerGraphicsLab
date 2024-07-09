#version 330 core

layout (location = 0) in vec3 inputPosition;
layout (location = 1) in vec3 inputNormal;
layout (location = 2) in vec2 inputTextureCoordinates;
layout (location = 3) in vec3 inputTangent;
layout (location = 4) in vec3 inputBitangent;

out VertexOutput {
    vec3 fragmentPosition;
    vec2 textureCoordinates;
    vec3 tangentLightSourcePosition;
    vec3 tangentViewPosition;
    vec3 tangentFragmentPosition;
} vertexOutput;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 lightSourcePosition;
uniform vec3 viewPosition;

void main()
{
    vertexOutput.fragmentPosition = vec3(model * vec4(inputPosition, 1.0));   
    vertexOutput.textureCoordinates = inputTextureCoordinates;
    
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(normalMatrix * inputTangent);
    vec3 N = normalize(normalMatrix * inputNormal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    
    mat3 TBN = transpose(mat3(T, B, N));    
    vertexOutput.tangentLightSourcePosition = TBN * lightSourcePosition;
    vertexOutput.tangentViewPosition  = TBN * viewPosition;
    vertexOutput.tangentFragmentPosition  = TBN * vertexOutput.fragmentPosition;
        
    gl_Position = projection * view * model * vec4(inputPosition, 1.0);
}

