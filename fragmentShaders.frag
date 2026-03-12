#version 330 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D emission;
	float shininess;
};

struct DirectionalLight {
	vec3 direction;

	vec3 color;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {

	vec3 position;

	vec3 color;

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

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 viewPos;

uniform Material material;

vec3 calculateDirectionalLight(DirectionalLight light);

vec3 calculatePointLight(PointLight light);

vec3 calculateSpotLight(SpotLight light);

vec3 getDiffuseLighting(vec3 norm, vec3 dir, vec3 lColor);

vec3 getSpecularLighting(vec3 norm, vec3 dir, vec3 lColor);

vec3 getLightingResults(vec3 lColor, vec3 lPos);

void main()
{
	vec3 result = vec3(0.0);


	result += calculateDirectionalLight(dirLight);
	for (int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		result += calculatePointLight(pointLights[i]);
	}
	//result += calculateSpotLight(spotLight);
	result *= vec3(texture(texture1, texCoord).xyz); // objColor;

	FragColor =  vec4(result, 1.0);
}

vec3 calculateDirectionalLight(DirectionalLight light)
{
	vec3 lightDir = normalize(-light.direction);
	vec3 norm = normalize(Normal);

	vec3 ambient = light.ambient * material.ambient * light.color;

	vec3 diffuse = light.diffuse * getDiffuseLighting(norm, lightDir, light.color);;

	vec3 specular = light.specular * getSpecularLighting(norm, lightDir, light.color);

	return ambient + diffuse + specular;

}

vec3 calculatePointLight(PointLight light)
{
	vec3 ambient = light.ambient * material.ambient * light.color;

	vec3 norm = normalize(Normal);
	vec3 dir = normalize(light.position - fragPos);

	float dist = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

	vec3 diffuse = light.diffuse * getDiffuseLighting(norm, dir, light.color);

	vec3 specular = light.specular * getSpecularLighting(norm, dir, light.color);

	return ((ambient * attenuation) + (diffuse * attenuation) + (specular * attenuation));
}

vec3 calculateSpotLight(SpotLight light)
{
	vec3 lightDir = light.position - fragPos;
	float theta = dot(lightDir, normalize(-light.direction));

	if (theta < light.cutOff)
	{
		return vec3(light.ambient * light.diffuse * material.ambient);
	}

	vec3 ambient = light.ambient * material.ambient * light.color;

	vec3 norm = normalize(Normal);
	float dist = length(light.position - fragPos);

	vec3 diffuse = light.diffuse * getDiffuseLighting(norm, lightDir, light.color);

	vec3 specular = light.specular * getSpecularLighting(norm, lightDir, light.color);

	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));


	return ((ambient) + (diffuse * attenuation) + (specular * attenuation));
}

vec3 getDiffuseLighting(vec3 norm, vec3 dir, vec3 lColor)
{
	
	float diff = max(dot(norm, dir), 0.0);
	vec3 diffuse = (diff * material.diffuse) * lColor;
	return diffuse;
}

vec3 getSpecularLighting(vec3 norm, vec3 dir, vec3 lColor)
{

	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-dir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	return (material.specular * spec) * lColor;
}
