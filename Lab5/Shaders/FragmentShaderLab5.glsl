#version 330 core

struct Material
{
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;

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

uniform vec3 cameraPosition;

void main()
{
	// ambient
	vec3 ambientColor = material.ambientColor * lightSource.ambientColor;
	
	// diffuse
	vec3 normal = normalize(normal);
	vec3 lightSourceDirection = normalize(lightSource.position - fragmentPosition);	
	//vec3 lightSourceDirection = normalize(-lightSource.direction); //	only for direcdtional light

	// A . B = |A| * |B| * cosθ ---- |A| and |B| equals 1 if they are unit vectors, which they are.
	float diffuseAngle = max(dot(lightSourceDirection, normal), 0);
	vec3 diffuseColor = diffuseAngle * lightSource.diffuseColor * material.diffuseColor;

	// specular 
	vec3 reflectedLightDirection = reflect(-lightSourceDirection, normal);
	vec3 viewerDirection = normalize(cameraPosition - fragmentPosition);

	float specularAngle = pow(max(dot(reflectedLightDirection, viewerDirection), 0), material.shininess);
	vec3 specularColor = specularAngle * lightSource.specularColor * material.specularColor;


	float distanceFromLightSource = length(lightSource.position - fragmentPosition);
	float attenuation = 1.0 / ( lightSource.constant + lightSource.linear * distanceFromLightSource +
								 lightSource.quadratic * distanceFromLightSource * distanceFromLightSource);

	ambientColor *= attenuation;
	diffuseColor *= attenuation;
	specularColor *= attenuation;

	vec3 finalColor = ambientColor + diffuseColor + specularColor;

	gl_FragColor = vec4(finalColor, 1.0);
}