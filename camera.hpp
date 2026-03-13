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


enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
};

class Camera
{
public:

	Camera(vec3 initialPos, vec3 iforward = vec3(0.0f, 0.0f, -1.0f), vec3 iup = vec3(0.0f, 1.0f, 0.0f), float initalZoom = 45.0f, float cameraSpeed = 2.5f, float yaw = -90, float pitch = 0.0)
	{
		position = initialPos;
		this->forward = iforward;
		worldUp = iup;

		zoom = initalZoom;
		this->cameraSpeed = cameraSpeed;
		this->yaw = yaw;
		this->pitch = pitch;

		updateVectors();
	}
	
	glm::mat4 getView() const
	{
		return glm::lookAt(position, position + forward, up);
	}

	void updateMovement(CameraMovement direction, float deltaTime)
	{
		if (direction == FORWARD)
			position += cameraSpeed * forward * deltaTime;
		else if (direction == LEFT)
			position -= cameraSpeed * glm::normalize(glm::cross(forward, worldUp)) * deltaTime;
		else if (direction == RIGHT)
			position += cameraSpeed * glm::normalize(glm::cross(forward, worldUp)) * deltaTime;
		else if (direction == BACKWARD)
			position -= cameraSpeed * forward * deltaTime;

	}

	void updateCameraForward(float xoffset, float yoffset)
	{
		const float sensitivity = 0.1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0) pitch = 89.0;
		if (pitch < -89.0) pitch = -89.0;

		updateVectors();
	}

	void updateCameraZoom(double xoffset, double yoffset)
	{
		zoom -= (float)yoffset;
		if (zoom < 1.0f) zoom = 1.0f;
		if (zoom > 45.0f) zoom = 45.0f;
	}

	void updateVectors()
	{
		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch)) * -1;
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		forward = glm::normalize(direction);
		right = glm::normalize(glm::cross(forward, worldUp));
		up = glm::normalize(glm::cross(right, forward));
	}

	const vec3 getPosition() const { return position; }

	void setPosition(vec3 pos) { position = pos; }

	const vec3 getForward() const { return forward; }

	const vec3& getRight() const { return  right; }
	
	const vec3& getUp() const { return up; }

	const float getZoom() const { return zoom; }


private:

	vec3 position;
	vec3 forward;
	vec3 up;
	vec3 right;
	vec3 worldUp;

	float yaw, pitch, zoom;

	float cameraSpeed;

};