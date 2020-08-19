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
	model player;
	vector<model> store;
	//Background object
	background.initProgram("stone.png");
	store.push_back(background);
	//Player Object
	player.config(GL_CLAMP_TO_EDGE);
	player.initProgram("awesomeface.png");
	store.push_back(player);

	for (size_t i = 0; i < 5; i++)
	{
		//scenery Object(s).
		model test;
		test.initProgram("awesomeface.png");
		glm::mat4 trans1 = glm::mat4(1.0f);
		trans1 = glm::translate(trans1, glm::vec3((float)i / 10, -0.5f, 0.0f));
		trans1 = glm::scale(trans1, glm::vec3(0.05, 0.05, 0.05));
		test.transform(trans1);
		store.push_back(test);
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

		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		trans = glm::scale(trans, glm::vec3(0.05, 0.05, 0.05));
		player.transform(trans);

		//player.draw();
		//background.draw();
		for (size_t i = 0; i < store.size(); i++)
		{			
			store[i].draw();
		}

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
