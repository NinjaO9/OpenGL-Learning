#version 330 core
out vec4 FragColor;

in vec3 fragPos;
in vec2 texCoord;
in vec3 Normal;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 objColor;
uniform vec3 lightColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	/*
	FragColor = mix(
			texture(texture1, texCoord), 
			texture(texture2, texCoord), 
			0.2);
	*/

	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	vec3 result = ambient * objColor;

	vec3 norm = normalize(Normal);
	vec3 dir = normalize(lightPos - fragPos);

	float diffuseStrength = 1.5;

	float diff = max(dot(norm, dir), 0.0);
	vec3 diffuse = diff * lightColor;
	diffuse = diffuse * diffuseStrength;

	float specularStrength = 0.5;

	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-dir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	result = (ambient + diffuse + specular) * vec3(texture(texture1, texCoord).xyz);
	FragColor =  vec4(result, 1.0);//vec4(lightColor * objColor, 1.0);

	//FragColor  = texture(texture1, texCoord);
	//FragColor = vec4(ourColor, 1.0f);

}