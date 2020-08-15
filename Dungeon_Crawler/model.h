#pragma once
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include "LoadShaders.h"
#include <iostream>
#include <vector>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>

class model
{
	public:
		GLuint VAO, textureID;
		int programID;
		std::vector<float>vertices;
		void initProgram(const char* str);
		void transform(glm::mat4 trans);
		void draw();
		void config(GLint textureType);
	private:
		//Config Variables:
		GLint textureType;
		void init();
		void loadTexture(const char* str);
};

