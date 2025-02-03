#ifndef JWNTRANSFORMMESH_H
#define JWNTRANSFORMMESH_H

#include "../../common.h"
#include "../../context.h"
#include "jwmStructs.h"

//7 wire colors: white, black, red, orange, yellow, green, blue
std::vector<glm::vec3> wireColors = {glm::vec3(1,1,1), glm::vec3(0,0,0), glm::vec3(1,0,0), 
glm::vec3(1, 0.65, 0), glm::vec3(1,1,0), glm::vec3(0,1,0), glm::vec3(0,0,1)};

void transformAndMeshWire(jumperWireModel& jwm, Context& context, Common& common, int index){

glm::vec3 color = wireColors[common.jumperWireTable[index].colorIndex];
float angle = getAngleFromPoints(jwm.lead1Pos2D.x, jwm.lead1Pos2D.y, jwm.lead2Pos2D.x, jwm.lead2Pos2D.y);
glm::mat3 rotationMatrix = getRotationMatrix(angle);
glm::vec3 a;
glm::vec3 b;

//Catenary sample points
for(int i = 0; i < 3; i++){
	a = glm::vec3(jwm.catenarySamplePoints[i].x, jwm.catenarySamplePoints[i].y, 0);
	b = glm::vec3(jwm.catenarySamplePoints[i + 1].x, jwm.catenarySamplePoints[i + 1].y, 0);

	a = rotationMatrix * a;
	b = rotationMatrix * b;	
	a += glm::vec3(jwm.wirePos.x, 0, jwm.wirePos.y);
	b += glm::vec3(jwm.wirePos.x, 0, jwm.wirePos.y);
	//pushV3(context.lVertexData, a);
	//pushV3(context.lVertexData, b);
	pushV3C3(context.lcVertexData, a, color);
	pushV3C3(context.lcVertexData, b, color);
}

//a0-a1, a1-a2 line segments
{
	a = glm::vec3(jwm.fc.a0.x, jwm.fc.a0.y, 0);
	b = glm::vec3(jwm.fc.a1.x, jwm.fc.a1.y, 0);
	
	a = rotationMatrix * a;
	b = rotationMatrix * b;	
	a += glm::vec3(jwm.wirePos.x, 0, jwm.wirePos.y);
	b += glm::vec3(jwm.wirePos.x, 0, jwm.wirePos.y);
	//pushV3(context.lVertexData, a);
	//pushV3(context.lVertexData, b);
	pushV3C3(context.lcVertexData, a, color);
	pushV3C3(context.lcVertexData, b, color);

	a = glm::vec3(jwm.fc.a1.x, jwm.fc.a1.y, 0);
	b = glm::vec3(jwm.fc.a2.x, jwm.fc.a2.y, 0);
	
	a = rotationMatrix * a;
	b = rotationMatrix * b;	
	a += glm::vec3(jwm.wirePos.x, 0, jwm.wirePos.y);
	b += glm::vec3(jwm.wirePos.x, 0, jwm.wirePos.y);
	//pushV3(context.lVertexData, a);
	//pushV3(context.lVertexData, b);
	pushV3C3(context.lcVertexData, a, color);
	pushV3C3(context.lcVertexData, b, color);
}

//Logit sample points
for(int i = 0; i < 3; i++){
	a = glm::vec3(jwm.logitSamplePoints[i].x, jwm.logitSamplePoints[i].y, 0);
	b = glm::vec3(jwm.logitSamplePoints[i + 1].x, jwm.logitSamplePoints[i + 1].y, 0);

	a = rotationMatrix * a;
	b = rotationMatrix * b;	
	a += glm::vec3(jwm.wirePos.x, 0, jwm.wirePos.y);
	b += glm::vec3(jwm.wirePos.x, 0, jwm.wirePos.y);
	//pushV3(context.lVertexData, a);
	//pushV3(context.lVertexData, b);
	pushV3C3(context.lcVertexData, a, color);
	pushV3C3(context.lcVertexData, b, color);
}

//Flipped catenary sample points
for(int i = 0; i < 3; i++){
	a = glm::vec3(jwm.flippedCatenarySamplePoints[i].x, jwm.flippedCatenarySamplePoints[i].y, 0);
	b = glm::vec3(jwm.flippedCatenarySamplePoints[i + 1].x, jwm.flippedCatenarySamplePoints[i + 1].y, 0);

	a = rotationMatrix * a;
	b = rotationMatrix * b;	
	a += glm::vec3(jwm.wirePos.x, 0, jwm.wirePos.y);
	b += glm::vec3(jwm.wirePos.x, 0, jwm.wirePos.y);
	//pushV3(context.lVertexData, a);
	//pushV3(context.lVertexData, b);
	pushV3C3(context.lcVertexData, a, color);
	pushV3C3(context.lcVertexData, b, color);
}

//flipped a0-a1, a1-a2 line segments
{
	a = glm::vec3(-jwm.fc.a0.x, jwm.fc.a0.y, 0);
	b = glm::vec3(-jwm.fc.a1.x, jwm.fc.a1.y, 0);
	
	a = rotationMatrix * a;
	b = rotationMatrix * b;	
	a += glm::vec3(jwm.wirePos.x, 0, jwm.wirePos.y);
	b += glm::vec3(jwm.wirePos.x, 0, jwm.wirePos.y);
	//pushV3(context.lVertexData, a);
	//pushV3(context.lVertexData, b);
	pushV3C3(context.lcVertexData, a, color);
	pushV3C3(context.lcVertexData, b, color);


	a = glm::vec3(-jwm.fc.a1.x, jwm.fc.a1.y, 0);
	b = glm::vec3(-jwm.fc.a2.x, jwm.fc.a2.y, 0);
	
	a = rotationMatrix * a;
	b = rotationMatrix * b;	
	a += glm::vec3(jwm.wirePos.x, 0, jwm.wirePos.y);
	b += glm::vec3(jwm.wirePos.x, 0, jwm.wirePos.y);
	//pushV3(context.lVertexData, a);
	//pushV3(context.lVertexData, b);
	pushV3C3(context.lcVertexData, a, color);
	pushV3C3(context.lcVertexData, b, color);
}

//flipped logit sample points
for(int i = 0; i < 3; i++){
	a = glm::vec3(jwm.flippedLogitSamplePoints[i].x, jwm.flippedLogitSamplePoints[i].y, 0);
	b = glm::vec3(jwm.flippedLogitSamplePoints[i + 1].x, jwm.flippedLogitSamplePoints[i + 1].y, 0);

	a = rotationMatrix * a;
	b = rotationMatrix * b;	
	a += glm::vec3(jwm.wirePos.x, 0, jwm.wirePos.y);
	b += glm::vec3(jwm.wirePos.x, 0, jwm.wirePos.y);
	//pushV3(context.lVertexData, a);
	//pushV3(context.lVertexData, b);
	pushV3C3(context.lcVertexData, a, color);
	pushV3C3(context.lcVertexData, b, color);
}

}
#endif