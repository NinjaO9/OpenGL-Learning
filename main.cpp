
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "shader.hpp"
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <random>

void framebudder_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window, Shader& shader);

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float lastX = 800;
float lastY = 600;

float yaw, pitch, zoom;

bool firstMouse = true;

int main(void)
{	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Oh my god its a moving camera", NULL, NULL);
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

	float verticies[] = {
		// Vertexes            // Colors            // Texture
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,// bottom left
		-0.5f, 0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,// top left
		0.5f, 0.5f, 0.0f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,// top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,// bottom right
	};

	float texCoords[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f
	};

	unsigned int indicies[] = {
		// back face
		3, 1, 0, 
		3, 2, 1,

		// front face
		7, 5, 4,
		7, 6, 5,

		// left face
		0, 3, 4,
		4, 7, 3,

		// right face
		1, 2, 5,
		5, 6, 2,

		// bottom face
		0, 1, 5,
		5, 6, 1,

		// top face
		2, 3, 6,
		6, 7, 3,


	};


	float verticesTest[] = { 
		-0.5f,-0.5f,-0.5f, 0.0f, 0.0f,
		0.5f,-0.5f,-0.5f,  1.0f, 0.0f,
		0.5f, 0.5f,-0.5f, 1.0f, 1.0f,

		-0.5f, -0.5f,-0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f,-0.5f, 0.0f,1.0f,
		0.5f, 0.5f,-0.5f, 1.0f,1.0f,

		-0.5f,-0.5f, 0.5f, 0.0f,0.0f,
		0.5f,-0.5f, 0.5f, 1.0f,0.0f,
		0.5f, 0.5f, 0.5f, 1.0f,1.0f,

		0.5f, 0.5f, 0.5f, 1.0f,1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f,1.0f,
		-0.5f,-0.5f, 0.5f, 0.0f,0.0f,

		-0.5f, 0.5f, 0.5f, 1.0f,0.0f,
		-0.5f, 0.5f,-0.5f, 1.0f,1.0f,
		-0.5f,-0.5f,-0.5f, 0.0f,1.0f,

		-0.5f,-0.5f,-0.5f, 0.0f,1.0f,
		-0.5f,-0.5f, 0.5f, 0.0f,0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f,0.0f,

		0.5f, 0.5f, 0.5f, 1.0f,0.0f,
		0.5f, 0.5f,-0.5f, 1.0f,1.0f,
		0.5f,-0.5f,-0.5f, 0.0f,1.0f,

		0.5f,-0.5f,-0.5f, 0.0f,1.0f,
		0.5f,-0.5f, 0.5f, 0.0f,0.0f,
		0.5f, 0.5f, 0.5f, 1.0f,0.0f,

		-0.5f,-0.5f,-0.5f, 0.0f,1.0f,
		0.5f,-0.5f,-0.5f, 1.0f,1.0f,
		0.5f,-0.5f, 0.5f, 1.0f,0.0f,

		0.5f,-0.5f, 0.5f, 1.0f,0.0f,
		-0.5f,-0.5f, 0.5f, 0.0f,0.0f,
		-0.5f,-0.5f,-0.5f, 0.0f,1.0f,

		-0.5f, 0.5f,-0.5f, 0.0f,1.0f,
		0.5f, 0.5f,-0.5f, 1.0f,1.0f,
		0.5f, 0.5f, 0.5f, 1.0f,0.0f,

		0.5f, 0.5f, 0.5f, 1.0f,0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f,0.0f,
		-0.5f, 0.5f,-0.5f, 0.0f,1.0f
	};

	int wWidth = 800, wHeight = 600;

	int iWidth, iHeight, nrChannels;

	unsigned int VBO[2];

	unsigned int VAO[2];

	unsigned int texture[2];

	unsigned int EBO[2];

	unsigned char* data = stbi_load("container.jpg", &iWidth, &iHeight, &nrChannels, 0);

	Shader shader("vertexShaders.vert", "fragmentShaders.frag");

	glViewport(0, 0, wWidth, wHeight); // initialize view of window

	glGenVertexArrays(2, VAO); // generate buffers for Vertex Array Objects

	glGenBuffers(1, EBO); // gen buffers for Element Buffer Objects

	glGenBuffers(2, VBO); // gen buffers for Vertex Buffer Objects

	glBindVertexArray(VAO[0]); // Use the Vertex Array Object at index 0 for the upcoming tasks

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); // Bind the Vertex Buffer Object to configure the current VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTest), verticesTest, GL_STATIC_DRAW); // Initialize the data inside the Vertex Buffer Object
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // Initalize an attribute for the VAO to know where this attribute (vertex positions) are in the VBO
	glEnableVertexAttribArray(0); // enable the atttributes

	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // Initalize ... (Colors)
	//glEnableVertexAttribArray(1); // enable

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // Initalize .. (Texture coordinates)
	glEnableVertexAttribArray(2); // enable

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]); // Use this Element Buffer Object to current VAO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW); // initialize information inside of EBO
	
	// Texture loading

	stbi_set_flip_vertically_on_load(true);

	glGenTextures(2, texture);

	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iWidth, iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Failed to generate texture 1" << endl;
	}
	stbi_image_free(data);

	data = stbi_load("awesome-face.png", &iWidth, &iHeight, &nrChannels, 0);

	glBindTexture(GL_TEXTURE_2D, texture[1]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iWidth, iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Failed to generate texture 2" << endl;
	}
	stbi_image_free(data);
	

	shader.use();
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);

	glEnable(GL_DEPTH_TEST);


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

	glm::mat4 view;


	while (!glfwWindowShouldClose(window))
	{
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;
		processInput(window, shader);
		

		glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.use();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glBindVertexArray(VAO[0]);


		glm::mat4 model(1.0f);
		time = glm::sin(glfwGetTime());
		tf = glGetUniformLocation(shader.ID, "transform");

		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		
		/*glm::mat4 view(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));*/

		float camX = sin(glfwGetTime() * radius);
		float camZ = cos(glfwGetTime() * radius);
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(zoom), wWidth / (float)wHeight, 0.1f, 100.0f);

		model = glm::rotate(model, glm::radians(50.0f) * (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

		//glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		////glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0,36);



		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model(1.0f);
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			if (i % 3 == 0)	model = glm::rotate(model, (float)glfwGetTime() * glm::radians(55.0f) * (i + 0.1f), glm::vec3(1.0f, 0.3f, 0.5f));

			glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
			//glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
			//glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

			glDrawArrays(GL_TRIANGLES, 0, 36);

		}

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
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

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
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch)) * -1;
	cameraFront = glm::normalize(direction);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	zoom -= (float)yoffset;
	if (zoom < 1.0f) zoom = 1.0f;
	if (zoom > 45.0f) zoom = 45.0f;

}

void processInput(GLFWwindow* window, Shader& shader)
{
	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cameraPos += cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		cameraPos -= cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
}

