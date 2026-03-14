#pragma once

#ifndef GLM_H
#define GLM_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif

using glm::vec3;

constexpr int CONSTANT = 1; // constant in attentuation formula

enum LIGHTS_ATTRIBUTES
{
	AMBIENCE,
	DIFFUSE,
	SPECULAR,
};

enum ATTENTUATION_ATTRIBUTES
{
	LINEAR = 3,
	QUADRATIC,
};

enum LIGHT_TYPE
{
	DIRECTIONAL,
	POINT,
	SPOT,
};

class Light
{
public:

	Light(vec3 color, LIGHT_TYPE ltype, float intensity = 1.0f, float line = 0.5f, float quad = 0.05f)
	{
		this->color = color;
		ambience = color * intensity;
		diffuse = color * intensity;
		specular = color * intensity;
		linear = line;
		quadratic = quad;

		type = ltype;
	}

	Light(vec3 ambi, vec3 diff, vec3 spec, LIGHT_TYPE ltype, float line = 0.5f, float quad = 0.05f)
	{
		this->color = diff;
		ambience = ambi;
		diffuse = diff;
		specular = spec;
		linear = line;
		quadratic = quad;

		type = ltype;
	}
	
	vec3 getAmbience() const { return ambience; }
	vec3 getDiffuse() const { return diffuse; }
	vec3 getSpecular() const { return specular; }

	void intensifyAmbience(float intensity = 1.0f) { this->ambience *= intensity; }
	void intensifyDiffuse(float intensity = 1.0f) { this->diffuse *= intensity; }
	void intensifySpecular(float intensity = 1.0f) { this->specular *= intensity; }

	vec3*& extractAttributes() const
	{
		vec3* attributes = new vec3[3];
		attributes[AMBIENCE] = ambience;
		attributes[DIFFUSE] = diffuse;
		attributes[SPECULAR] = specular;
		return attributes;
	}

	vec3 color;

	float linear;
	float quadratic;

private:

	vec3 ambience;
	vec3 diffuse;
	vec3 specular;

	LIGHT_TYPE type;

};