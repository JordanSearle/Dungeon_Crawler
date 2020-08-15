#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include "LoadShaders.h"
#include <iostream>
#include "model.h"



using namespace std;

GLFWwindow* window;
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//Takes the Users Inputs
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


int main()
{
	glfwInit();
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Dunegon Crawler", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glEnable(GL_DEPTH_TEST);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glewInit();
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//Main render loop


	model background;	
	model tests;
	tests.textureType = GL_CLAMP_TO_EDGE;
	background.textureType = GL_REPEAT;
	std:vector<model> store;
	store.push_back(tests);
	store.push_back(background);

	float testVertices[] = {
		//X   Y   Z
		 // positions          // colors           // texture coords
	 0.5f,  0.5f, -1.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,  // top right
	 0.5f, -0.5f, -1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, -1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	-0.5f,  0.5f, -1.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f     // top left  
	};
	std::vector<float> temp(testVertices, testVertices + sizeof testVertices / sizeof testVertices[0]);

	tests.vertices = temp;
	tests.initProgram("container.jpg");
	background.initProgram("stone.png");
	for (int i = 0; i < tests.vertices.size(); i++)
	{
		cout << tests.vertices[i] << " " << background.vertices[i] << endl;
	}

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		
		glClearBufferfv(GL_COLOR, 0, black);
		glClear(GL_COLOR_BUFFER_BIT);
		// bind textures on corresponding texture units
		glEnable(GL_DEPTH_TEST);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		tests.draw();
		background.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwDestroyWindow(window);

	glfwTerminate();
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.

	cout << width << " " << height << endl;
	glViewport(0, 0, width, height);
}
