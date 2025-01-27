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

	std::vector<float> tVertexData; //use: textured triangles only, reserved for circuit elements
	std::vector<float> lVertexData; //use: line segments only
	std::vector<float> oVertexData; //use: textured triangles only, reserved for breadboard, ICs
	std::vector<float> cVertexData; //use: colored triangles only

	unsigned int tVAO;
	unsigned int tVBO;

	unsigned int lVAO;
	unsigned int lVBO;

	unsigned int oVAO;
	unsigned int oVBO;

	unsigned int cVAO;
	unsigned int cVBO;	

	Shader textureShader;
	Shader lineShader;
	Shader colorShader;
	

	Texture elementTexture;
	Texturef breadboardTexture;
	Texture icTexture;

	Camera camera;	

};

Context context;

#endif