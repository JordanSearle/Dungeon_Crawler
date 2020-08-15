#pragma once
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include "LoadShaders.h"
#include <iostream>

class model
{
	public:
		GLuint VAO;
		int programID;
		GLuint textureID;
		void loadTexture(const char* str);
		void init();
		void draw();
		void initProgram();
};

