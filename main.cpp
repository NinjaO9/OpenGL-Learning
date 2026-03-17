
#ifndef GLAD_H
#define GLAD_H
#include <glad/glad.h>
#endif
#include <glfw/glfw3.h>

#include "shader.hpp"
#include "texture2D.hpp"
#include "camera.hpp"
#include "model.hpp"

#ifndef IMGUI_H 
#define IMGUI_H
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"
#endif


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

bool activeMouse = true;

float lastX, lastY;
Camera camera(vec3(0.0f, 0.0f, 3.0f));

glm::vec3 lightPos(1.5f, 2.0f, 2.0f);

float cLightRadius = 2.5f;
glm::vec3 rotationalCenter(0.0f, 1.0f, 0.0f);

vec3 mLPos1 = vec3(0.0f, 0.0f, 0.0f);
vec3 mLPos2 = vec3(0.0f, 0.0f, 0.0f);
float mLightRadius = 1.5f;
glm::vec3 mLRCenter(0.0f, 0.0f, 0.0f);

float cTheta = 0.0f;

float mTheta = 0.0f;

int wWidth = 1600, wHeight = 1200;

int main(void)
{	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(wWidth, wHeight, "Oh my god its an obsidian block", NULL, NULL);
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
			// positions          // normal           // tex coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	float bverts[] =
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

	unsigned int VBO[2];

	unsigned int VAO[3];

	unsigned int EBO;

	Shader shader("vertexShaders.vert", "fragmentShaders.frag");

	glViewport(0, 0, wWidth, wHeight); // initialize view of window

	glGenVertexArrays(3, VAO); // generate buffers for Vertex Array Objects

	glGenBuffers(2, VBO); // gen buffers for Vertex Buffer Objects

	glBindVertexArray(VAO[0]); // Use the Vertex Array Object at index 0 for the upcoming tasks

	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); // Bind the Vertex Buffer Object to configure the current VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Initialize the data inside the Vertex Buffer Object
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // Initalize an attribute for the VAO to know where this attribute (vertex positions) are in the VBO
	glEnableVertexAttribArray(0); // enable the atttributes

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // Initalize ... (Normals)
	glEnableVertexAttribArray(1); // enable

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // Initalize .. (Texture coordinates)
	glEnableVertexAttribArray(2); // enable


	glBindVertexArray(0);
	glBindVertexArray(VAO[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); // same vertex info as the other VAO

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	
	// Texture loading
	stbi_set_flip_vertically_on_load(true);

	//Texture2D texture1("Obsidian.jpg");
	//Texture2D texture2("Obsidian_Specular.jpg");

	shader.use();


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



	//texture1.activate(GL_TEXTURE0);
	//texture1.bind();
	//texture2.activate(GL_TEXTURE1);
	//texture2.bind();

	vec3 sunCol = vec3(1.0f, 1.0f, 1.0f);
	vec3 mLColor1 = vec3(1.0f, 0.0f, 1.0f);
	vec3 mLColor2 = vec3(0.0f, 1.0f, 0.0f);

	



	// Initalize IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();  (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	Light mainLight(sunCol, DIRECTIONAL);
	mainLight.intensifyAmbience(0.005f);
	Light magicLight1(mLColor1, POINT);
	magicLight1.intensifyAmbience(0.2f);
	Light magicLight2(mLColor2, POINT);
	magicLight2.intensifyAmbience(0.2f);
	Light spotLight(vec3(0.0f), SPOT);

	
	Model backpack("backpack/backpack.obj");

	while (!glfwWindowShouldClose(window))
	{
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;
		processInput(window, shader);

		mTheta = currentTime * 1.2;
		mLPos1 = vec3(mLRCenter.x + (mLightRadius * sin(mTheta)), mLightRadius * ((cos(mTheta)) / 1.5 + (sin(mTheta)) / 1.5), mLRCenter.z + (mLightRadius * cos(mTheta)));
		mLPos2 = vec3(mLRCenter.x + (mLightRadius * sin(mTheta * 1.5)), mLRCenter.y + (mLightRadius * cos(mTheta * 1.5)), mLightRadius * ((cos(mTheta * 1.5))/1.5));

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("OpenGL Edit box");
		ImGui::SliderFloat("Magic Light1 ColorR: ", &mLColor1.x, 0, 1);
		ImGui::SliderFloat("Magic Light1 ColorG: ", &mLColor1.y, 0, 1);
		ImGui::SliderFloat("Magic Light1 ColorB: ", &mLColor1.z, 0, 1);
		ImGui::End();
		magicLight1.setColor(mLColor1);
		// Main object
		shader.use();

		glBindVertexArray(VAO[0]);
		
		shader.setVec3("viewPos", camera.getPosition());


		// Material config
		shader.setVec3("material.ambient", vec3(0.5, 0.5, 0.5));
		shader.setInt("material.diffuseMap", 0);
		shader.setInt("material.specularMap", 1);
		shader.setFloat("material.shininess", 32);

		shader.setLight("dirLight", mainLight);

		shader.setLight("pointLights[0]", magicLight1);
		shader.setFloat("pointLights[0].constant", 1.0f);
		shader.setFloat("pointLights[0].linear", 0.09f);
		shader.setFloat("pointLights[0].quadratic", 0.032f);

		shader.setLight("pointLights[1]", magicLight2);
		shader.setFloat("pointLights[1].constant", 1.0f);
		shader.setFloat("pointLights[1].linear", 0.09f);
		shader.setFloat("pointLights[1].quadratic", 0.032f);
		
		shader.setLight("spotLight", spotLight);
		shader.setVec3("spotLight.position", camera.getPosition());
		shader.setVec3("spotLight.direction", camera.getForward());
		shader.setFloat("spotLight.cutOff", cos(glm::radians(12.5f)));
		shader.setFloat("spotLight.outerCutOff", cos(glm::radians(17.5f)));
		shader.setFloat("spotLight.constant", 1.0f);
		shader.setFloat("spotLight.linear", 0.09f);
		shader.setFloat("spotLight.quadratic", 0.032f);
		


		glm::mat4 view;
		view = camera.getView();

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera.getZoom()), wWidth / (float)wHeight, 0.1f, 100.0f);


		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		glm::mat4 model(1.0f);

		model = glm::translate(glm::mat4(1.0f), cubePositions[0]);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		shader.setMat4("model", model);

		//for (int i = 0; i < 10; i++)
		//{

		//	model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
		//	model = glm::rotate(model, float(glm::radians(45.0f) * glfwGetTime()), vec3(0.2f, 0.6f, 0.1f));
		//	shader.setMat4("model", model);

		//	glm::mat3 tiModel(glm::transpose(glm::inverse(model)));

		//	shader.setMat3("tiModel", tiModel);

		//	shader.setVec3("dirLight.direction", cubePositions[i] - lightPos);
		//	shader.setVec3("pointLights[0].position", mLPos1);
		//	shader.setVec3("pointLights[1].position", mLPos2);


		//	//glDrawArrays(GL_TRIANGLES, 0, 36);
		//}

		glm::mat3 tiModel(glm::transpose(glm::inverse(model)));

		shader.setMat3("tiModel", tiModel);
		shader.setVec3("dirLight.direction", cubePositions[0] - lightPos);
		shader.setVec3("pointLights[0].position", mLPos1);
		shader.setVec3("pointLights[1].position", mLPos2);
		backpack.Draw(shader);


		glBindVertexArray(0);

		

		// "sun"

		glBindVertexArray(VAO[1]);
		lightShader.use();
		lightShader.setMat4("view", view);
		lightShader.setMat4("projection", projection);
		model = glm::translate(glm::mat4(1.0f), lightPos);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		lightShader.setMat4("model", model);
		lightShader.setVec3("color", sunCol);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);


		// Little lights
		// uses the same light shader, just changes some things
		glBindVertexArray(VAO[1]);
		model = glm::translate(glm::mat4(1.0f), mLPos1);
		model = glm::scale(model, glm::vec3(0.25, 0.25, 0.25));
		lightShader.setMat4("model", model);
		lightShader.setVec3("color", mLColor1);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::translate(glm::mat4(1.0f), mLPos2);
		model = glm::scale(model, glm::vec3(0.25, 0.25, 0.25));
		
		lightShader.setMat4("model", model);
		lightShader.setVec3("color", mLColor2);


		glDrawArrays(GL_TRIANGLES, 0, 36);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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
	if (!activeMouse) return;
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
	
	camera.updateCameraForward(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.updateCameraZoom(xoffset, yoffset);
}

void processInput(GLFWwindow* window, Shader& shader)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && activeMouse)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		activeMouse = false;
	}
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS && !activeMouse)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		activeMouse = true;
	}
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
		camera.updateMovement(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.updateMovement(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.updateMovement(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.updateMovement(RIGHT, deltaTime);
	}


	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		// revolve light left
		cTheta -= 1.0f * deltaTime;
		lightPos.x = rotationalCenter.x + (cLightRadius * cos(cTheta));
		lightPos.z = rotationalCenter.z + (cLightRadius * sin(cTheta));
	}


	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		// revolve light right
		cTheta += 1.0f * deltaTime;
		lightPos.x = rotationalCenter.x + (cLightRadius * cos(cTheta));
		lightPos.z = rotationalCenter.z + (cLightRadius * sin(cTheta));
	}


}