#ifndef TESTS_H
#define TESTS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "context.h"
#include "common.h"
#include "./netlist/readFile.h"
#include "./netlist/mapNetlist.h"
#include "./construct/icPlace.h"
#include "./construct/elementPlace.h"
#include "./construct/bookkeeping.h"
#include "./mesh/meshBreadboard.h"
#include "./mesh/proceduralBreadboard.h"

void readContext(Context& context){
	std::cout << "Context window width: " << context.windowWidth << std::endl;
}

void setReadCommon(Common& common){
	common.netlistVector.resize(1);
	common.netlistVector[0].push_back("Netlist Vector Item");
	std::cout << common.netlistVector[0][0] << std::endl;
	common.netlistVector.clear();
}

void breadboardCodePos(){
	glm::vec2 p1 = getPosition(65, 0, 0);
	std::cout << "p1: " << p1.x << " " << p1.y << " top left";
 	std::cout << "  calculated: 0.25 0.25" << std::endl;

	p1 = getPosition(65, 1, 1);
	std::cout << "p2: " << p1.x << " " << p1.y << " top left--";
	std::cout << "  calculated: 0.75 0.75" << std::endl;

	p1 = getPosition(65, 0, 58);
	std::cout << "p3: " << p1.x << " " << p1.y << " top right" << std::endl;

	p1 = getPosition(70, 0, 0);
	std::cout << "p4: " << p1.x << " " << p1.y << " bottom left" << std::endl;

	p1 = getPosition(70, 0, 58);
	std::cout << "p5: " << p1.x << " " << p1.y << " bottom right" << std::endl;

	p1 = getPosition(70, 2, 0);
	std::cout << "p6: " << p1.x << " " << p1.y << " random";
	std::cout << "  calculated: 0.25 7.75" << std::endl;

	p1 = getPosition(65, 2, 0);
	std::cout << "p7: " << p1.x << " " << p1.y << " random";
	std::cout << "  calculated: 0.25 2.25" << std::endl;

}

void rotateVector(){
	float pi = 3.14159265358;
	glm::vec3 v;
	glm::mat3 rot;

	rot = getRotationMatrix(pi / 2.f);
	v = rot * glm::vec3(1, 0, 0);
	std::cout << "90 deg rotation, Vec: (1, 0, 0) -> (";
	std::cout << v.x << ", " << v.y << ", " << v.z << ") ?= (0, 0, 1)" << std::endl;

	rot = getRotationMatrix(pi);
	v = rot * glm::vec3(1, 0, 0);
	std::cout << "180 deg rotation, Vec: (1, 0, 0) -> (";
	std::cout << v.x << ", " << v.y << ", " << v.z << ") ?= (-1, 0, 0)" << std::endl;

	rot = getRotationMatrix(3.f*pi/2.f);
	v = rot * glm::vec3(1, 0, 0);
	std::cout << "270 deg rotation, Vec: (1, 0, 0) -> (";
	std::cout << v.x << ", " << v.y << ", " << v.z << ") ?= (0, 0, -1)" << std::endl;
}

void angleFromPoints(){
	float angle;
	
	angle = getAngleFromPoints(0, 0, 1, 0);
	std::cout << "(0,0) (1,0) -> angle: " << angle << " ?= 0" << std::endl;
	
	angle = getAngleFromPoints(0, 0, 0, 1);
	std::cout << "(0,0) (0,1) -> angle: " << angle << " ?= 1.5708" << std::endl;

	angle = getAngleFromPoints(0, 0, -1, 0);
	std::cout << "(0,0) (-1,0) -> angle: " << angle << " ?= 3.14" << std::endl;

	angle = getAngleFromPoints(0, 0, 0, -1);
	std::cout << "(0,0) (0,-1) -> angle: " << angle << " ?= 4.712" << std::endl;

	angle = getAngleFromPoints(-0.5, -0.5, 0.5, 0.5);
	std::cout << "(-0.5,-0.5) (0.5,0.5) -> angle: " << angle << " ?= 0.785" << std::endl;

}

void midpointFromPoints(){
	glm::vec2 m;

	m = getMidpoint2D(-0.5, -0.5, 0.5, 0.5);
	std::cout << "midpoint: " << m.x << ", " << m.y << std::endl;

	m = getMidpoint2D(0, 0, 20, 0);
	std::cout << "midpoint: " << m.x << ", " << m.y << std::endl;

	m = getMidpoint2D(0, 0, 0, 20);
	std::cout << "midpoint: " << m.x << ", " << m.y << std::endl;

}

void distanceTest(){
	float dist = getDistance(glm::vec2(0, 0), glm::vec2(3, 4));
	std::cout << "dist: " << dist << std::endl;
}

void readFileTest(Common& common, const char* fn){ //make sure that the path is relative to the executable!
	readFile(common, fn);
	
	//Point to note: It seems the last string in each row contains a new line character at the end. 
	for(int i = 0; i < common.netlistVector.size(); i++){
		std::cout << "{ ";
		for(int j = 0; j < common.netlistVector[i].size(); j++){
			std::cout << "{\"" << common.netlistVector[i][j] << "\"} ";
		}
		std::cout << " }  Size: " << common.netlistVector[i].size() << std::endl;
	}
}

void mapNetlistTest(Common& common){
	readFile(common, "netlistTest.txt");	
	mapNetlist(common);

	//nodeMap
	std::cout << "std::unordered_map<std::string, int> nodeMap: " << std::endl;
	std::unordered_map<std::string, int>::iterator it;
	for(it = common.nodeMap.begin(); it != common.nodeMap.end(); it++){
		std::cout << it->first << " -> " << it->second << std::endl;
	}
	std::cout << std::endl;
	
	//netlist vector element char check
	char type = common.netlistVector[1][0][0];
	bool c1 = (type == 'R');
	std::cout << "char R == 'R' ? " << c1 << std::endl;
	std::cout << std::endl;	

	//Element table
	std::cout << "std::vector<elementTableRow> elementTable: " << std::endl;
	for(int i = 0; i < common.elementTable.size(); i++){
		std::cout << "Type: " << common.elementTable[i].type << " Nodes: " << common.elementTable[i].nodes[0] << " " << common.elementTable[i].nodes[1] << std::endl;
	}
	std::cout << std::endl;

	//Node Table
	std::cout << "std::vector<nodeTableRow> elementTable: " << std::endl;
	std::cout << "Not needed in the application at the moment, but will be useful in the future. " << std::endl;
	for(int i = 0; i < common.nodeTable.size(); i++){
		std::cout << "Type: " << common.nodeTable[i].type << "  Nodes: ";
	
		for(int j = 0; j < common.nodeTable[i].elements.size(); j++){
			std::cout << common.nodeTable[i].elements[j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	//VCC and GND Node values
	std::cout << "VCC and GND node values: " << std::endl;
	std::cout << "VCC: " << common.vccNode << std::endl;
	std::cout << "GND: " << common.groundNode << std::endl;
	std::cout << std::endl;
	
}

void printBreadboard(Common& common){
	//Print the entire breadboard to console output
	for(int i = 0; i < 59; i++){
		/*printf("%02d %+d %02d %02d %02d %02d %02d %02d %02d %+d %02d %02d %02d %02d %02d %02d %02d\n", i, 
		common.breadboardRailDescriptorArrayF[i], 
		common.breadboardOccupancyMatrixF[i][0],
		common.breadboardOccupancyMatrixF[i][1],
		common.breadboardOccupancyMatrixF[i][2],
		common.breadboardOccupancyMatrixF[i][3],
		common.breadboardOccupancyMatrixF[i][4],
		common.breadboardOccupancyMatrixF[i][5],
		common.breadboardOccupancyMatrixF[i][6],
		common.breadboardRailDescriptorArrayA[i], 
		common.breadboardOccupancyMatrixA[i][6],
		common.breadboardOccupancyMatrixA[i][5],
		common.breadboardOccupancyMatrixA[i][4],
		common.breadboardOccupancyMatrixA[i][3],
		common.breadboardOccupancyMatrixA[i][2],
		common.breadboardOccupancyMatrixA[i][1],
		common.breadboardOccupancyMatrixA[i][0]	
		);*/

		printf("%02d ", common.breadboardRailDescriptorArrayF[i]);
		if(common.breadboardOccupancyMatrixF[i][0]){ printf("XX ");} 
		else{ printf("   "); }
		if(common.breadboardOccupancyMatrixF[i][1]){ printf("XX ");} 
		else{ printf("   "); }
		if(common.breadboardOccupancyMatrixF[i][2]){ printf("XX ");} 
		else{ printf("   "); }
		if(common.breadboardOccupancyMatrixF[i][3]){ printf("XX ");} 
		else{ printf("   "); }
		if(common.breadboardOccupancyMatrixF[i][4]){ printf("XX ");} 
		else{ printf("   "); }
		if(common.breadboardOccupancyMatrixF[i][5]){ printf("XX ");} 
		else{ printf("   "); }
		if(common.breadboardOccupancyMatrixF[i][6]){ printf("XX ");} 
		else{ printf("   "); }
		printf("%02d ", common.breadboardRailDescriptorArrayA[i]);
		if(common.breadboardOccupancyMatrixA[i][6]){ printf("XX ");} 
		else{ printf("   "); }
		if(common.breadboardOccupancyMatrixA[i][5]){ printf("XX ");} 
		else{ printf("   "); }
		if(common.breadboardOccupancyMatrixA[i][4]){ printf("XX ");} 
		else{ printf("   "); }
		if(common.breadboardOccupancyMatrixA[i][3]){ printf("XX ");} 
		else{ printf("   "); }
		if(common.breadboardOccupancyMatrixA[i][2]){ printf("XX ");} 
		else{ printf("   "); }
		if(common.breadboardOccupancyMatrixA[i][1]){ printf("XX ");} 
		else{ printf("   "); }
		if(common.breadboardOccupancyMatrixA[i][0]){ printf("XX ");} 
		else{ printf("   "); }
		printf("\n");
	}
	printf("\n\n\n");
}

void icPlaceTest(Common& common){
	readFile(common, "netlistTest.txt");	
	mapNetlist(common);
	icPlace(common);
	
	printBreadboard(common);

}

void elementPlaceTest(Common& common){
	readFile(common, "netlistTest.txt");
	mapNetlist(common);
	icPlace(common);	

	//placeElement(common, 3, 5, 0); //passed	
	//placeElement(common, 4, 0, 1);	//passed - copy-pasting mistake was the cause of failure!
	//placeElement(common, 5, 1, 2); //passed
	//placeElement(common, 2, 6, 3); //passed :: failed on 01/25 - need to allocate node if v1 or v2 is empty. 
	//placeElement(common, 6, 0, 4); //passed
	//placeElement(common, 1, 0, 5); //passsed
	//printBreadboard(common);	

	for(int i = 0; i < common.elementTable.size(); i++){
		placeElement(common, common.elementTable[i].nodes[0], common.elementTable[i].nodes[1], i);
		breadboardCheck(common);				
	}
	printBreadboard(common);		
}

void appInitTest(Context& context){
	glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		context.window = glfwCreateWindow(context.windowWidth, context.windowHeight, context.windowName.c_str(), nullptr, nullptr);
		if(context.window == nullptr){
			std::cout << "Window could not be created. " << std::endl;
			return;
		}
		glfwMakeContextCurrent(context.window);
		glfwSetInputMode(context.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        		std::cout << "Failed to initialize GLAD. " << std::endl;
        		return;
    		}
		
		glEnable(GL_DEPTH_TEST);

		//Set shaders, textures, camera
		context.textureShader = Shader("./breadboard3D/mesh/shaders/tVertex.vs", "./breadboard3D/mesh/shaders/tFragment.fs", true);
		context.colorShader = Shader("./breadboard3D/mesh/shaders/lVertex.vs", "./breadboard3D/mesh/shaders/lFragment.fs", true);
		context.elementTexture = Texture(" ");
		generateBreadboardTexture(context, common);
		context.camera = Camera(context.window);
		context.camera.cameraSpeed = 20.f;
}

void meshBreadboardTest(Common& common, Context& context){
	appInitTest(context);

	readFile(common, "netlistTest.txt");
	mapNetlist(common);
	icPlace(common);	

	for(int i = 0; i < common.elementTable.size(); i++){
		placeElement(common, common.elementTable[i].nodes[0], common.elementTable[i].nodes[1], i);
		breadboardCheck(common);				
	}
	printBreadboard(common);		
	
	//Print the element code. 	
	std::cout << std::endl;
	for(int i = 0; i < common.elementTable.size(); i++){
		std::cout << "Element [" << i << "] code: ";
		for(int j = 0; j < 6; j++){
			std::cout << common.elementTable[i].code[j] << " ";
		}
		std::cout << std::endl;	
	}
	
	meshBreadboard(common, context);
	
	std::cout << "textured vertex data size: " << context.tVertexData.size() << std::endl;
	for(int i = 0; i < 6; i++){
		std::cout << context.tVertexData[i*5 + 0] << " ";
		std::cout << context.tVertexData[i*5 + 1] << " ";
		std::cout << context.tVertexData[i*5 + 2] << " ";
		std::cout << context.tVertexData[i*5 + 3] << " ";
		std::cout << context.tVertexData[i*5 + 4] << " ";
		std::cout << std::endl;
	}

	std::cout << "inline static element vertices v1: " << std::endl;
	std::cout << elementVertices::v1.x << " " << elementVertices::v1.y << " " << elementVertices::v1.z << std::endl;

	std::cout << "calculated vertices: " << std::endl;
	glm::vec2 lead1Pos2D = getPosition(65, 5, 1);
	glm::vec2 lead2Pos2D = getPosition(65, 5, 2);
	glm::vec2 elementPos2D = getMidpoint2D(lead1Pos2D.x, lead1Pos2D.y, lead2Pos2D.x, lead2Pos2D.y);
	glm::vec3 elementPos3D = glm::vec3(elementPos2D.x, 5.f, elementPos2D.y);
	float xzAngle = getAngleFromPoints(lead1Pos2D.x, lead1Pos2D.y, lead2Pos2D.x, lead2Pos2D.y);
	glm::mat3 rotationMatrix = getRotationMatrix(xzAngle);
	glm::vec3 v1 = (rotationMatrix * elementVertices::v1) + elementPos3D;

}

#endif