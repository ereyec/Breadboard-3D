#ifndef CONTEXT_H
#define CONTEXT_H

#include <vector>
#include <string>

#include "../include/engine/Camera.h"
#include "../include/engine/Shader.h"
#include "../include/engine/Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Context{
	GLFWwindow* window = nullptr;

	unsigned int windowWidth = 1200;
	unsigned int windowHeight = 900;
	std::string windowName = "Breadboard 3D";	

	std::vector<float> tVertexData;
	std::vector<float> lVertexData;
	std::vector<float> oVertexData;

	unsigned int tVAO;
	unsigned int tVBO;
	unsigned int lVAO;
	unsigned int lVBO;
	unsigned int oVAO;
	unsigned int oVBO;

	Shader textureShader;
	Shader colorShader;
	Texture elementTexture;
	Texturef breadboardTexture;
	Camera camera;	

};

Context context;

#endif