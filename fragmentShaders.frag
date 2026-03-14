#version 330 core

struct Material {
	vec3 ambient;
	sampler2D diffuseMap;
	sampler2D specularMap;
	sampler2D emission;
	float shininess;
};

struct DirectionalLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {

	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	vec3 color;
	float cutOff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

#define NR_POINT_LIGHTS 2
uniform PointLight pointLights[NR_POINT_LIGHTS];

uniform DirectionalLight dirLight;

uniform SpotLight spotLight;

out vec4 FragColor;

in vec3 fragPos;
in vec2 texCoord;
in vec3 Normal;

uniform vec3 viewPos;

uniform Material material;

vec3 calculateDirectionalLight(DirectionalLight light, vec3 norm);

vec3 calculatePointLight(PointLight light, vec3 norm);

vec3 calculateSpotLight(SpotLight light, vec3 norm);

vec3 getDiffuseLighting(vec3 norm, vec3 dir, vec3 ldiffuse);

vec3 getSpecularLighting(vec3 norm, vec3 dir, vec3 lspecular);

void main()
{
	vec3 result = vec3(0.0);
	vec3 norm = normalize(Normal);


	result += calculateDirectionalLight(dirLight, norm);
	for (int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		result += calculatePointLight(pointLights[i], norm);
	}
	result += calculateSpotLight(spotLight, norm);
	//result += vec3(texture(material.emission, texCoord).xyz); // Commented out cause I am not using any emmision maps
	FragColor =  vec4(result, 1.0);
}

vec3 calculateDirectionalLight(DirectionalLight light, vec3 norm)
{
	vec3 lightDir = normalize(-light.direction);

	vec3 ambient = light.ambient * vec3(texture(material.diffuseMap, texCoord));

	vec3 diffuse = getDiffuseLighting(norm, lightDir, light.diffuse);

	vec3 specular = getSpecularLighting(norm, lightDir, light.specular);

	return ambient + diffuse + specular;

}

vec3 calculatePointLight(PointLight light, vec3 norm)
{
	vec3 ambient = light.ambient * vec3(texture(material.diffuseMap, texCoord));

	vec3 dir = normalize(light.position - fragPos);

	float dist = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

	vec3 diffuse = getDiffuseLighting(norm, dir, light.diffuse);

	vec3 specular = getSpecularLighting(norm, dir, light.specular);

	return ((ambient * attenuation) + (diffuse * attenuation) + (specular * attenuation));
}

vec3 calculateSpotLight(SpotLight light, vec3 norm)
{
	vec3 lightDir = normalize(light.position - fragPos);
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	vec3 ambient = light.ambient * vec3(texture(material.diffuseMap, texCoord).xyz);

	float dist = length(light.position - fragPos);

	vec3 diffuse = getDiffuseLighting(norm, lightDir, light.diffuse) * intensity;

	vec3 specular = getSpecularLighting(norm, lightDir, light.specular) * intensity;

	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));


	return ((ambient) + (diffuse * attenuation) + (specular * attenuation));
}

vec3 getDiffuseLighting(vec3 norm, vec3 dir, vec3 ldiffuse)
{
	
	float diff = max(dot(norm, dir), 0.0);
	vec3 diffuse = ldiffuse * diff * vec3(texture(material.diffuseMap, texCoord));
	return diffuse;
}

vec3 getSpecularLighting(vec3 norm, vec3 dir, vec3 lspecular)
{

	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-dir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	return (texture(material.specularMap, texCoord).xyz * spec) * lspecular;
}
