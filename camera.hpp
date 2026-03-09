#ifndef GLAD_H
#define GLAD_H
#include <glad/glad.h>
#endif

#ifndef GLM_H
#define GLM_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif
using glm::vec3;

#ifndef GENERICS_H
#define GENERICS_H
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#endif



class Camera
{
public:

	Camera(vec3 initialPos, vec3 iforward = vec3(0.0f, 0.0f, -1.0f), vec3 iup = vec3(0.0f, 1.0f, 0.0f), float initalZoom = 45.0f, float cameraSpeed = 2.5f)
	{
		position = initialPos;
		this->forward = iforward;
		this->up = iup;

		zoom = initalZoom;
		this->cameraSpeed = cameraSpeed;
		yaw = 0;
		pitch = 0;

		lastX = 800;
		lastY = 600;


	}

	void goForward(float dt) { position += cameraSpeed * dt * forward; }

	void goBackwards(float dt) { position -= cameraSpeed * dt * forward; }

	void goLeft(float dt) { position -= cameraSpeed * dt * glm::normalize(glm::cross(forward, up)); }

	void goRight(float dt) { position += cameraSpeed * dt * glm::normalize(glm::cross(forward, up)); }

	void updateCameraForward(float xpos, float ypos)
	{
		float xoffset = xpos - lastX;
		float yoffset = ypos - lastY;
		lastX = xpos;
		lastY = ypos;

		const float sensitivity = 0.1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0) pitch = 89.0;
		if (pitch < -89.0) pitch = -89.0;

		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch)) * -1;
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		forward = glm::normalize(direction);
	}

	void updateCameraZoom(double xoffset, double yoffset)
	{
		zoom -= (float)yoffset;
		if (zoom < 1.0f) zoom = 1.0f;
		if (zoom > 45.0f) zoom = 45.0f;
	}

	const vec3& getPosition() const { return position; }

	const vec3& getForward() const { return forward; }
	
	const vec3& getUp() const { return up; }

	const float getZoom() const { return zoom; }

private:

	vec3 position;
	vec3 forward;
	vec3 up;

	float yaw, pitch, zoom;

	float cameraSpeed;

	float lastX, lastY;

};