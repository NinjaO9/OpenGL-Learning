
#ifndef GLAD_H
#define GLAD_H
#include <glad/glad.h>
#endif
#include <glfw/glfw3.h>

#include "shader.hpp"
#include "texture2D.hpp"
#include "camera.hpp"
//#include "stb_image.h"

#ifndef GLM_H
#define GLM_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif

#include <random>

void framebudder_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window, Shader& shader);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool firstMouse = true;

Camera camera(vec3(0.0f, 0.0f, 3.0f));

glm::vec3 lightPos(1.5f, 1.0f, 2.0f);

float cLightRadius = 2.5f;
glm::vec3 rotationalCenter(0.0f, 0.0f, 0.0f);

float theta = 0.0f;

int main(void)
{	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Oh my god its cool lighting", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebudder_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initalize GLAD" << endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	float vertices[] = {
			// positions		// normal
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	float cverts[] =
	{
		-0.5f, -0.5f, 1.0f,  0.0f, 0.0f, // bottom left
		-0.5f, 0.5f, 1.0f,  0.0f, 1.0f, // top left
		0.5f, -0.5f, 1.0f,  1.0f, 0.0f, //bottom right
		0.5f, 0.5f, 1.0f,   1.0f, 1.0f, // top right
	};

	unsigned int indicies[] =
	{
		0, 1, 2,
		1, 3, 2,
	};

	int wWidth = 800, wHeight = 600;

	unsigned int VBO[2];

	unsigned int VAO[2];

	unsigned int EBO;

	Shader shader("vertexShaders.vert", "fragmentShaders.frag");

	glViewport(0, 0, wWidth, wHeight); // initialize view of window

	glGenVertexArrays(2, VAO); // generate buffers for Vertex Array Objects

	glGenBuffers(2, VBO); // gen buffers for Vertex Buffer Objects

	glBindVertexArray(VAO[0]); // Use the Vertex Array Object at index 0 for the upcoming tasks

	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); // Bind the Vertex Buffer Object to configure the current VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Initialize the data inside the Vertex Buffer Object
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // Initalize an attribute for the VAO to know where this attribute (vertex positions) are in the VBO
	glEnableVertexAttribArray(0); // enable the atttributes

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Initalize ... (Normals)
	glEnableVertexAttribArray(1); // enable

	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Initalize .. (Texture coordinates)
	//glEnableVertexAttribArray(2); // enable


	glBindVertexArray(0);
	glBindVertexArray(VAO[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); // same vertex info as the other VAO

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	
	// Texture loading
	stbi_set_flip_vertically_on_load(true);

	Texture2D texture1("container.jpg", 0, GL_RGB, GL_RGB);
	Texture2D texture2("awesome-face.png", 0, GL_RGB, GL_RGBA);

	shader.use();
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);

	Shader lightShader("lightvs.vert", "lightfs.frag");


	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, 100);

	float time = 0;
	unsigned int tf = 0;

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 5.0f,-15.0f),
		glm::vec3(-1.5f,-2.2f,-2.5f),
		glm::vec3(-3.8f,-2.0f,-12.3f),
		glm::vec3(2.4f,-0.4f,-3.5f),
		glm::vec3(-1.7f, 3.0f,-7.5f),
		glm::vec3(1.3f,-2.0f,-2.5f),
		glm::vec3(1.5f, 2.0f,-2.5f),
		glm::vec3(1.5f, 0.2f,-1.5f),
		glm::vec3(-1.3f, 1.0f,-1.5f)
	};

	const float radius = 10.0f;



	texture1.activate(GL_TEXTURE0);
	texture1.bind();
	texture2.activate(GL_TEXTURE1);
	texture2.bind();

	vec3 objCol = vec3(1.0f, 0.5f, 0.31f);
	shader.setVec3("objColor", objCol);
	vec3 lightCol = vec3(1.0f, 1.0f, 1.0f);
	shader.setVec3("lightColor", lightCol);


	while (!glfwWindowShouldClose(window))
	{
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;
		processInput(window, shader);
		

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.use();

		glBindVertexArray(VAO[0]);
		

		shader.setVec3("lightPos", lightPos);

		glm::mat4 view;
		view = glm::lookAt(camera.getPosition(), camera.getPosition() + camera.getForward(), camera.getUp());

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera.getZoom()), wWidth / (float)wHeight, 0.1f, 100.0f);


		shader.setMat4("view", view);
		shader.setMat4("projection", projection);


		glm::mat4 model(1.0f);

		model = glm::translate(glm::mat4(1.0f), cubePositions[0]);
		shader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);

		glBindVertexArray(VAO[1]);
		lightShader.use();
		lightShader.setMat4("view", view);
		lightShader.setMat4("projection", projection);
		model = glm::translate(glm::mat4(1.0f), lightPos);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		lightShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		

		glfwSwapBuffers(window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	glfwTerminate();
	return 0;
}


void framebudder_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	camera.updateCameraForward(xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.updateCameraZoom(xoffset, yoffset);
}

void processInput(GLFWwindow* window, Shader& shader)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.goForward(deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.goBackwards(deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.goLeft(deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.goRight(deltaTime);
	}


	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		// revolve light left
		theta -= 1.0f * deltaTime;
		lightPos.x = rotationalCenter.x + (cLightRadius * cos(theta));
		lightPos.z = rotationalCenter.z + (cLightRadius * sin(theta));
	}


	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		// revolve light right
		theta += 1.0f * deltaTime;
		lightPos.x = rotationalCenter.x + (cLightRadius * cos(theta));
		lightPos.z = rotationalCenter.z + (cLightRadius * sin(theta));
	}


}

