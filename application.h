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
			std:cerr << "Window could not be created. " << std::endl;
			exit(-1);
		}
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        		std::cerr << "Failed to initialize GLAD. " << std::endl;
        		exit(-1);
    		}
		return 0;
	}

	void run(Context& context);

	void cleanup(){}

};

void Application::run(Context& context, Common& common){

readFile(common, "netlistExample.txt");
mapNetlist(common);
icPlace(common);

for(int i = 0; i < common.elementTable.size(); i++){
	placeElement(common, common.elementTable[i].nodes[0], common.elementTable[i].nodes[1], i);
	breadboardCheck(common);
}

meshBreadboard(common, context);

}


#endif