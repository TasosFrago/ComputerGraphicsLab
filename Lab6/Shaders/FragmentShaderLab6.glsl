#version 330 core

struct Material
{
	sampler2D container2Texture;
	sampler2D container2SpecularTexture;

	float shininess;
};

uniform Material material;

struct LightSource
{
	//vec3 direction; // only for direcdtional light
	vec3 position;

	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;

	float constant;
	float linear;
	float quadratic;
};

uniform LightSource lightSource;

in vec3 normal;
in vec3 fragmentPosition;
in vec2 textureCoordiantes;

uniform vec3 cameraPosition;

//uniform sampler2D containerTexture;
//uniform sampler2D awesomeFaceTexture;

float mixAmount = 0.5;

void main()
{
	// ambient
//	vec3 ambientColor = mix(texture(containerTexture, textureCoordiantes),
//							  texture(awesomeFaceTexture, textureCoordiantes), mixAmount).rgb * lightSource.ambientColor;

	vec3 ambientColor = texture(material.container2Texture, textureCoordiantes).rgb * lightSource.ambientColor;
	
	// diffuse
	vec3 normal = normalize(normal);
	vec3 lightSourceDirection = normalize(lightSource.position - fragmentPosition);	
	//vec3 lightSourceDirection = normalize(-lightSource.direction); //	only for direcdtional light

	// A . B = |A| * |B| * cosθ ---- |A| and |B| equals 1 if they are unit vectors, which they are.
	float diffuseAngle = max(dot(lightSourceDirection, normal), 0);
//	vec3 diffuseColor = diffuseAngle * lightSource.diffuseColor * mix(texture(containerTexture, textureCoordiantes),
//								          texture(awesomeFaceTexture, textureCoordiantes), mixAmount).rgb * lightSource.ambientColor;

	vec3 diffuseColor = diffuseAngle * lightSource.diffuseColor * texture(material.container2Texture, textureCoordiantes).rgb;

	// specular 
	vec3 reflectedLightDirection = reflect(-lightSourceDirection, normal);
	vec3 viewerDirection = normalize(cameraPosition - fragmentPosition);

	float specularAngle = pow(max(dot(reflectedLightDirection, viewerDirection), 0), material.shininess);
//	vec3 specularColor = specularAngle * lightSource.specularColor * mix(texture(containerTexture, textureCoordiantes),
//									     texture(awesomeFaceTexture, textureCoordiantes), mixAmount).rgb * lightSource.ambientColor;

	vec3 specularColor = specularAngle * lightSource.specularColor * texture(material.container2SpecularTexture, textureCoordiantes).rgb;


	float distanceFromLightSource = length(lightSource.position - fragmentPosition);
	float attenuation = 1.0 / ( lightSource.constant + lightSource.linear * distanceFromLightSource +
								 lightSource.quadratic * distanceFromLightSource * distanceFromLightSource);

	ambientColor *= attenuation;
	diffuseColor *= attenuation;
	specularColor *= attenuation;

	vec3 finalColor = ambientColor + diffuseColor + specularColor;

	gl_FragColor = vec4(finalColor, 1.0);
}