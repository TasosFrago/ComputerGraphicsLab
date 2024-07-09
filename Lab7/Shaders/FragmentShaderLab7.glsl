#version 330 core

out vec4 FragColor;

in VertexOutput {
    vec3 fragmentPosition;
    vec2 textureCoordinates;
    vec3 tangentLightSourcePosition;
    vec3 tangentViewPosition;
    vec3 tangentFragmentPosition;
} fragmentInput;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;

uniform vec3 lightSourcePosition;
uniform vec3 viewPosition;

void main()
{           
     // obtain normal from normal map in range [0,1]
    vec3 normal = texture(normalMap, fragmentInput.textureCoordinates).rgb;
    // transform normal vector to range [-1,1]
    normal = normalize(normal * 2.0 - 1.0);  // this normal is in tangent space
   
    // get diffuse color
    vec3 color = texture(diffuseMap, fragmentInput.textureCoordinates).rgb;
    // ambient
    vec3 ambient = 0.1 * color;
    // diffuse
    vec3 lightDir = normalize(fragmentInput.tangentLightSourcePosition - fragmentInput.tangentFragmentPosition);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    // specular
    vec3 viewDir = normalize(fragmentInput.tangentViewPosition - fragmentInput.tangentFragmentPosition);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

    vec3 specular = vec3(0.2) * spec;
    FragColor = vec4(ambient + diffuse + specular, 1.0);
}

