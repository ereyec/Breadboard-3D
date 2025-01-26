#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <stdlib.h>

#include "common.h"
#include "context.h"
#include "./netlist/readFile.h"
#include "./netlist/mapNetlist.h"
#include "./construct/icPlace.h"
#include "./construct/elementPlace.h"
#include "./construct/bookkeeping.h"
#include "./mesh/meshBreadboard.h"
#include "./mesh/proceduralBreadboard.h"

class Application{
public:	

	Application(){}

	int init(Context& context){
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		context.window = glfwCreateWindow(context.windowWidth, context.windowHeight, context.windowName.c_str(), nullptr, nullptr);
		if(context.window == nullptr){
			std::cout << "Window could not be created. " << std::endl;
			return -1;
		}
		glfwMakeContextCurrent(context.window);
		glfwSetInputMode(context.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        		std::cout << "Failed to initialize GLAD. " << std::endl;
        		return -1;
    		}
		
		glEnable(GL_DEPTH_TEST);

		//Set shaders, textures, camera
		context.textureShader = Shader("./breadboard3D/mesh/shaders/tVertex.vs", "./breadboard3D/mesh/shaders/tFragment.fs", true);
		context.colorShader = Shader("./breadboard3D/mesh/shaders/lVertex.vs", "./breadboard3D/mesh/shaders/lFragment.fs", true);
		context.elementTexture = Texture("resistor.png");
		generateBreadboardTexture(context, common);
		context.camera = Camera(context.window);
		context.camera.cameraSpeed = 20.f;

		return 0;
	}

	void run(Context& context, Common& common);

	void cleanup(Context& context);

private:
	float lastFrame = 0.0f;
	float deltaTime = 0.0f;

};

void Application::run(Context& context, Common& common){

readFile(common, "netlistTest.txt");
mapNetlist(common);
icPlace(common);

for(int i = 0; i < common.elementTable.size(); i++){
	placeElement(common, common.elementTable[i].nodes[0], common.elementTable[i].nodes[1], i);
	breadboardCheck(common);
}

meshBreadboard(common, context);

while (!glfwWindowShouldClose(context.window)){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.227f, 0.4f, 0.6f, 1.0f);
	
	float currentFrame = glfwGetTime();
        this->deltaTime = currentFrame - this->lastFrame;
        this->lastFrame = currentFrame;
	
	context.camera.update(this->deltaTime);

	//Render
	glm::mat4 view = glm::lookAt(context.camera.cameraPos, context.camera.cameraPos + context.camera.cameraFront, context.camera.cameraUp);
        glm::mat4 projection = glm::perspective(45.0f, 1200.0f / 900.0f, 0.1f, 400.0f);
	
	glUseProgram(context.textureShader.ID);
	glUniformMatrix4fv(glGetUniformLocation(context.textureShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(context.textureShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));

	glBindTexture(GL_TEXTURE_2D, context.breadboardTexture.ID);
	glBindVertexArray(context.oVAO);
	glDrawArrays(GL_TRIANGLES, 0, context.oVertexData.size() / 5);

	glBindTexture(GL_TEXTURE_2D, context.elementTexture.ID);
	glBindVertexArray(context.tVAO);
	glDrawArrays(GL_TRIANGLES, 0, context.tVertexData.size() / 5);

	glUseProgram(context.colorShader.ID);
	glUniformMatrix4fv(glGetUniformLocation(context.colorShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(context.colorShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));

	glBindVertexArray(context.lVAO);
	glDrawArrays(GL_LINES, 0, context.lVertexData.size() / 3);
	
	glfwSwapBuffers(context.window);
        glfwPollEvents();

}

}

void Application::cleanup(Context& context){
	glDeleteVertexArrays(1, &context.tVAO);
	glDeleteBuffers(1, &context.tVBO);

	glDeleteVertexArrays(1, &context.lVAO);
	glDeleteBuffers(1, &context.lVBO);

	glDeleteVertexArrays(1, &context.oVAO);
	glDeleteBuffers(1, &context.oVBO);

	glfwTerminate();
}


#endif