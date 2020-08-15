#pragma once
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include "LoadShaders.h"
#include <iostream>
#include <vector>

class model
{
	public:
		GLuint VAO, textureID;
		int programID;
		std::vector<float>vertices;
		void initProgram();
		void draw();
	private:
		void init();
		void loadTexture(const char* str);
};

