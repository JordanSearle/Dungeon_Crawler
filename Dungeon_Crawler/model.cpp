#include "model.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void model::loadTexture(const char* str)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureType);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureType);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char* data = stbi_load(str, &width, &height, &nrChannels, 0); 	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void model::init()
{
	unsigned int VBO, EBO;
	//If the vertices are undefined
	if (vertices.size() == 0)
	{
		float storeVertices[] = {
			//X   Y   Z
			 // positions          // colors           // texture coords
		 1.f,  1.f, 0.0f,   1.0f, 0.0f, 0.0f,   5.0f, 5.0f,   // top right
		 1.f, -1.f, 0.0f,   0.0f, 1.0f, 0.0f,   5.0f, -5.0f,   // bottom right
		-1.f, -1.f, 0.0f,   0.0f, 0.0f, 1.0f,   -5.0f, -5.0f,   // bottom left
		-1.f,  1.f, 0.0f,   1.0f, 1.0f, 0.0f,   -5.0f, 5.0f    // top left  
		};
		std::vector<float> temp(storeVertices, storeVertices + sizeof storeVertices / sizeof storeVertices[0]);
		vertices = temp;
	}

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),&vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void model::draw()
{
	glUseProgram(programID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void model::initProgram(const char* str)
{
	//Sets the Shader Locations and passes it to the class
	ShaderInfo  shaders[] = {
			{ GL_VERTEX_SHADER, "media/triangles.vert" },
			{ GL_FRAGMENT_SHADER, "media/triangles.frag" },
			{ GL_NONE, NULL }
	};
	//Inits the display Model

	//Load Program
	programID = LoadShaders(shaders);
	glUseProgram(programID);

	glGenVertexArrays(1, &VAO);
	init();
	loadTexture(str);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
